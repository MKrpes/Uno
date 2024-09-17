#include "pch.h"
#include "View.h"
#include"Resource.h"
#include <string>


IMPLEMENT_DYNCREATE(View, CView)
BEGIN_MESSAGE_MAP(View, CView)
    ON_WM_CREATE()
    ON_BN_CLICKED(1001, &View::OnDrawButtonClick)
    ON_BN_CLICKED(1002, &View::OnSkipButtonClick)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



View::~View()
{
    if (!hand_bitmaps.empty())
    {
        hand_bitmaps.clear();
    }
}


void View::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // Load the image from the resource using GDI+ Bitmap::FromResource
    if (!LoadImagesFromResource())
    {
        AfxMessageBox(_T("Failed to load the image resource"));
    }
    Invalidate();
}


BOOL View::LoadImagesFromResource()
{
    HMODULE hModule = AfxGetInstanceHandle();
    // Clear existing images
    for (auto img : hand_bitmaps)
    {
        delete img;
    }
    hand_bitmaps.clear();



    for (Card card : game->getPlayerhand()) {
        hand_bitmaps.push_back(Gdiplus::Bitmap::FromResource(hModule, MAKEINTRESOURCEW(card.Color*100+card.Type)));
    }

    // Redraw the view
    return TRUE;
}

void View::OnMouseMove(UINT nFlags, CPoint point) 
{
    bool hoverChanged = false;
    CRect hand;
    GetHandRect(hand);
    // Check if the mouse is hovering over an image
    if (hand.PtInRect(point)) {
        for (int i = 0; i < m_imageRects.size(); ++i)
        {
            if (m_imageRects[i].PtInRect(point)) 
            {
                // If the hovered image changed, update it
                if (m_hoveredImageIndex != i)
                {
                    hoverChanged = true;

                    // Invalidate the preview area for redrawing
                    CRect previewRect;
                    GetPreviewRect(previewRect);
                    InvalidateRect(previewRect, FALSE);  // Redraw only the preview area

                    m_hoveredImageIndex = i;
                }
                break;
            }
        }
    }

    // If no image is hovered, reset the hover index
    if (!hoverChanged && m_hoveredImageIndex != -1 && !m_imageRects[m_hoveredImageIndex].PtInRect(point))
    {
        hoverChanged = true;

        // Invalidate the preview area to clear the previous preview
        CRect previewRect;
        GetPreviewRect(previewRect);
        InvalidateRect(previewRect, FALSE);

        m_hoveredImageIndex = -1;
    }

    // If the hover state changed, trigger a redraw
    if (hoverChanged)
    {
        UpdateWindow();  // Force the view to be redrawn
    }

    CView::OnMouseMove(nFlags, point);
}

afx_msg int View::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Create a button
    DrawButton.Create(_T("Draw"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(300, 300, 400, 330), this, 1001);

    SkipButton.Create(_T("Uno"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(200, 200, 300, 230), this, 1002);

    // Force a redraw to display the loaded image
    CRect rect(10, 10, 200, 250);

    // Create the listbox with necessary styles
    m_ListBox.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_HASSTRINGS | WS_DISABLED, rect, this, 1001);

    // Add some items to the listbox
    CString str;
    str.Format(_T("You: %u"), game->getPlayerhand().size());
    m_ListBox.AddString(str);
    for (UINT i = 1; i < game->playerCount; ++i) {
        str.Format(_T("opponent %u: %u"), i, game->players[i]->playerHand->hand.size());
        m_ListBox.AddString(str);
    }
    return 0;
}


void View::OnDrawButtonClick()
{
    if(game->currentPlayer == 0 && !game->players[0]->hasDrawn && game->drawSum==0)
    {
        game->DrawCard();
        Invalidate();
    }
    else if(game->currentPlayer == 0 && !game->players[0]->hasDrawn && game->drawSum!=0)
    {
        game->drawSumDraw();
        Invalidate();
    }
}

void View::OnSkipButtonClick()
{
    if (game->currentPlayer == 0 && game->players[0]->hasDrawn)
    {
        game->PlayerMove(-1);
        game->GameGlow();
        m_ListBox.ResetContent();
        CString str;
        str.Format(_T("You: %u"), game->getPlayerhand().size());
        m_ListBox.AddString(str);
        for (UINT i = 1; i < game->playerCount; ++i) {
            str.Format(_T("opponent %u: %u"), i, game->players[i]->playerHand->hand.size());
            m_ListBox.AddString(str);
        }

        Invalidate();


    }
}

afx_msg void View::OnLButtonDown(UINT nFlags, CPoint point) {
   

    if (m_hoveredImageIndex > -1 &&
        m_hoveredImageIndex < hand_bitmaps.size() &&
        game->currentPlayer == 0)
    {
        switch (game->validatePlayerMove(m_hoveredImageIndex)) {
        case -1:{
            break;
        }
        case 0: {
            game->PlayerMove(m_hoveredImageIndex);
            Invalidate();
            break;
        }
        case 1: {
            ChooseColorDlg chooseDlg;
            if (chooseDlg.DoModal() == IDOK) {
                int color = chooseDlg.getChosenColor();
                game->PlayerMove(m_hoveredImageIndex,color);
                Invalidate();
            }
            break;
        }
        }
        game->GameGlow();
        m_ListBox.ResetContent();
        CString str;
        str.Format(_T("You: %d"), game->getPlayerhand().size());
        m_ListBox.AddString(str);
        for (UINT i = 1; i < game->playerCount; ++i) {
            str.Format(_T("opponent %d: %d"), i, game->players[i]->playerHand->hand.size());
            m_ListBox.AddString(str);
        }

        Invalidate();

    }
}





void View::ShowPlayedCard(CDC* pDC, const Card card) const {
    HMODULE hModule = AfxGetInstanceHandle();
    Gdiplus::Bitmap* pImage = Gdiplus::Bitmap::FromResource(hModule, MAKEINTRESOURCEW(card.Color * 100 + card.Type));

    if (pImage)
    {
        Graphics graphics(pDC->GetSafeHdc());

        CRect clientRect;
        GetClientRect(&clientRect);

        int previewWidth = 100;   //!!!test!!! change later
        int previewHeight = 200;  

        int xOffset = clientRect.right / 2 - previewWidth;  //!!!test!!! change later
        int yOffset = clientRect.bottom / 2 - previewHeight;  

        graphics.DrawImage(pImage, xOffset, yOffset, previewWidth, previewHeight);
    }
}

void View::loadGame(Game* gm)
{
    game = gm;
}

void View::OnDraw(CDC* pDC)
{
    // Create a memory DC to perform double buffering
    CRect clientRect;
    GetClientRect(&clientRect);

    CDC memoryDC;
    memoryDC.CreateCompatibleDC(pDC);

    // Create a bitmap compatible with the screen DC
    CBitmap bitmap;
    bitmap.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());

    // Select the bitmap into the memory DC
    CBitmap* pOldBitmap = memoryDC.SelectObject(&bitmap);

    // Fill the memory DC with a background color (optional)
    memoryDC.FillSolidRect(&clientRect, RGB(255, 255, 255)); // White background

    // Use GDI+ to draw into the memory DC
    Graphics graphics(memoryDC.GetSafeHdc());
    if (!hand_bitmaps.empty())
    {
        ShowHand(&memoryDC);
        ShowPlayedCard(&memoryDC, game->playedCards->getLast());
        // If an image is being hovered, display a larger preview
        if (m_hoveredImageIndex >= 0 && m_hoveredImageIndex < hand_bitmaps.size())
        {
            ShowPreview(&memoryDC, hand_bitmaps[m_hoveredImageIndex]);
        }
    }
    pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &memoryDC, 0, 0, SRCCOPY);

    // Cleanup: Select the old bitmap back into the memory DC and delete the objects
    memoryDC.SelectObject(pOldBitmap);
}


void View::ShowPreview(CDC* pDC, Gdiplus::Bitmap* pImage)
{
    if (pImage)
    {
        Graphics graphics(pDC->GetSafeHdc());

        // Define the preview area (for example, top of the client area)
        CRect clientRect;
        GetPreviewRect(clientRect);


        int previewWidth = clientRect.Width();  //!!!test!!! change later
        int previewHeight = clientRect.Height();

        int xOffset = clientRect.right - previewWidth;  // Right side of the window
        int yOffset = 20;  // Top of the window

        // Draw the enlarged preview of the hovered image
        graphics.DrawImage(pImage, xOffset, yOffset, previewWidth-20, previewHeight-20);
    }
}

void View::GetPreviewRect(CRect& previewRect) const
{
    // Define the preview area (example: top-right corner)
    CRect clientRect;
    GetClientRect(&clientRect);

    int previewWidth = clientRect.Width()/4;   // Width of the enlarged preview
    int previewHeight = clientRect.Height()/4;  // Height of the enlarged preview

    int xOffset = clientRect.right - previewWidth;  // Place on the right
    int yOffset = 20;  // Top of the window

    // Set the calculated preview rectangle
    previewRect = CRect(xOffset, yOffset, xOffset + previewWidth, yOffset + previewHeight);
}

void View::ShowHand(CDC* pDC)
{
    if (!game->getPlayerhand().empty())
    {
        LoadImagesFromResource();
        std::vector<UINT> cardsToEnlarge;
        if (game->drawSum == 0) {
            cardsToEnlarge=game->players[0]->playerHand->CheckForAvailableCards(game->playedCards->getLast());
        }
        else {
            cardsToEnlarge = game->players[0]->playerHand->CheckForStackingCards(game->playedCards->getLast());
        }
        m_imageRects.clear();

        Graphics graphics(pDC->GetSafeHdc());

        // Define the preview area (for example, top of the client area)
        CRect clientRect;
        GetHandRect(clientRect);

        int xOffset = 0;  // Horizontal position to start drawing
        //int imageWidth = clientRect.Width() / hand_bitmaps.size();
        //int imageHeight = clientRect.Height() / 2;
        int enCount = cardsToEnlarge.size();
        for (int i = 0; i < hand_bitmaps.size(); ++i)
        {
            UINT imageWidth = clientRect.Width() / (hand_bitmaps.size()-cardsToEnlarge.size()+2*cardsToEnlarge.size());

            UINT imageHeight = clientRect.Height();
            Gdiplus::Bitmap* pImage = hand_bitmaps[i];
            if (pImage)
            {
                imageHeight/=2; 
                if (pImage->GetWidth() / 2 < imageWidth) { //prevents cards from taking the entire screen
                    imageWidth = pImage->GetWidth() / 2;
                }

                for (UINT j : cardsToEnlarge)
                {
                    if (j == i) {
                        imageWidth *= 2;
                        imageHeight=clientRect.Height();
                        if (pImage->GetWidth() < imageWidth) { //prevents cards from taking the entire screen
                            imageWidth = pImage->GetWidth();
                        }
                        break;
                    }
                }

                int yOffset = clientRect.bottom - imageHeight; // Leave space for image row

                // Draw the image at the bottom
                graphics.DrawImage(pImage, xOffset, yOffset, imageWidth, imageHeight);
               // Store the image's position (for click and hover detection)
                CRect imageRect(xOffset, yOffset, xOffset + imageWidth, clientRect.bottom);
                m_imageRects.push_back(imageRect);

                // Increment the horizontal offset for the next image
                xOffset += imageWidth;  // Add some padding between images
            }
            int previewWidth = clientRect.Width();  //!!!test!!! change later
            int previewHeight = clientRect.Height();

            int xOffset = clientRect.right - previewWidth - 20;  // Right side of the window
            int yOffset = 20;  // Top of the window

        }
    }
}


void View::GetHandRect(CRect& handViewRect) const
{
    CRect clientRect;
    GetClientRect(&clientRect);

    int previewWidth = clientRect.Width();   // Width of the enlarged preview
    int previewHeight = clientRect.Height()/3;  // Height of the enlarged preview

    int xOffset = 0;  
    int yOffset = clientRect.Height()*0.66;

    // Set the calculated preview rectangle
    handViewRect = CRect(xOffset, yOffset, xOffset + previewWidth, yOffset + previewHeight);
}

BOOL View::OnEraseBkgnd(CDC* pDC)
{
    // Prevents background from being erased to reduce flickering
    return TRUE;
}