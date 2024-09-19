#include "pch.h"
#include "View.h"
#include"Resource.h"


IMPLEMENT_DYNCREATE(View, CView)
BEGIN_MESSAGE_MAP(View, CView)
    ON_WM_CREATE()
    ON_BN_CLICKED(1001, &View::OnDrawButtonClick)
    ON_BN_CLICKED(1002, &View::OnSkipButtonClick)
    ON_BN_CLICKED(1003, &View::OnUnoButtonClick)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
END_MESSAGE_MAP()

View::View(Game gm) : game(gm){
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
    for (auto img : hand_bitmaps)
    {
        delete img;
    }
    hand_bitmaps.clear();
    for (Card card : game.getPlayerhand()) {
        hand_bitmaps.push_back(Gdiplus::Bitmap::FromResource(hModule, MAKEINTRESOURCEW(card.Color*100+card.Type)));
    }

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


    DrawButton.Create(_T("Draw"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(0, 265, 100, 295), this, 1001);

    SkipButton.Create(_T("Skip"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(0, 225, 100, 255), this, 1002);

    UnoButton.Create(_T("Uno"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(0, 315, 100, 345), this, 1003);

    // Force a redraw to display the loaded image
    CRect rect(10, 10, 200, 220);

    // Create the listbox with necessary styles
    playerListBox.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_HASSTRINGS | WS_DISABLED, rect, this, NULL);
    UpdateListBox();

    return 0;
}


void View::OnDrawButtonClick()
{
    if (game.currentPlayer == 0 && !game.players[0].hasDrawn && game.drawSum == 0)
    {
        game.DrawCard();
        UpdateListBox();

        Invalidate();
        UpdateWindow();
    }
    else if (game.currentPlayer == 0 && !game.players[0].hasDrawn && game.drawSum != 0)
    {
        game.drawSumDraw();
        UpdateListBox();

        Invalidate();
        UpdateWindow();
    }
}


void View::OnSkipButtonClick()
{
    if (game.currentPlayer == 0 && game.players[0].hasDrawn)
    {
        game.PlayerMove(-1);
        ::SetTimer(*this, MyTimerId, 1000, NULL);

    }
}

void View::OnUnoButtonClick()
{
    isUno = true;
}

afx_msg void View::OnLButtonDown(UINT nFlags, CPoint point) {
   

    if (m_hoveredImageIndex > -1 &&
        m_hoveredImageIndex < hand_bitmaps.size() &&
        game.currentPlayer == 0)
    {        
        switch (game.validatePlayerMove(m_hoveredImageIndex)) {
        case -1: {
            break; //invalid move, nothing happens
        }
        case 0: {
            if (game.PlayerMove(m_hoveredImageIndex)) {
                ShowWinScreen(game.currentPlayer, game.UpdatePoints());
                break;
            }
            m_hoveredImageIndex = -1;
            Invalidate();
            break;
            }
        case 1: {
            ChooseColorDlg chooseDlg;
            if (chooseDlg.DoModal() == IDOK) {
                int color = chooseDlg.getChosenColor();
                    if (game.PlayerMove(m_hoveredImageIndex, color)) {
                ShowWinScreen(game.currentPlayer, game.UpdatePoints());
                break;
            }
                m_hoveredImageIndex = -1;
                Invalidate();
                break;
                }     
            }
        }
        if (!isUno && game.getPlayerhand().size() <= 1) {
            AfxMessageBox(_T("Uno not called"));
            game.PlayerUNOdraw();
            Invalidate();
            UpdateWindow();
        }
        isUno = false;
        if (game.currentPlayer != 0) {
            ::SetTimer(*this, MyTimerId, 1000, NULL);
        }
    }
}

void View::ShowPlayedCard(CDC* pDC,const Card card) const {
    HMODULE hModule = AfxGetInstanceHandle();
    Gdiplus::Bitmap* pImage = Gdiplus::Bitmap::FromResource(hModule, MAKEINTRESOURCEW(card.getColor() * 100 + card.getType()));

    if (pImage)
    {
        Graphics graphics(pDC->GetSafeHdc());

        CRect clientRect;
        GetClientRect(&clientRect);

        int previewWidth = pImage->GetWidth()*0.75;   
        int previewHeight = pImage->GetHeight()*0.75;  

        int xOffset = clientRect.right / 2 - previewWidth;  
        int yOffset = clientRect.bottom / 2 - previewHeight;  

        graphics.DrawImage(pImage, xOffset, yOffset, previewWidth, previewHeight);
    }
    else {
    }
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
    ShowPlayedCard(&memoryDC, game.playedCards.getLast());
    if (!hand_bitmaps.empty())
    {
        ShowHand(&memoryDC);
        
        // If an image is being hovered, display a larger preview
        if (m_hoveredImageIndex >= 0 && m_hoveredImageIndex < hand_bitmaps.size())
        {
            ShowPreview(&memoryDC, hand_bitmaps[m_hoveredImageIndex]);
        }
    }
    pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &memoryDC, 0, 0, SRCCOPY);

    // Cleanup: Select the old bitmap back into the memory DC and delete the objects
    memoryDC.SelectObject(pOldBitmap);
    DeleteObject(pOldBitmap);
    DeleteDC(memoryDC);
}


void View::ShowPreview(CDC* pDC, Gdiplus::Bitmap* pImage)const 
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
    int previewHeight = clientRect.Height()/2;  // Height of the enlarged preview

    int xOffset = clientRect.right - previewWidth;  // Place on the right
    int yOffset = 20;  // Top of the window

    // Set the calculated preview rectangle
    previewRect = CRect(xOffset, yOffset, xOffset + previewWidth, yOffset + previewHeight);
}



void View::UpdateListBox()
{
    playerListBox.ResetContent();
    CString str;
    str.Format(_T("You: %u cards, %d points"), game.getPlayerhand().size(), game.scBoard.GetPlayerPoints(0));
    playerListBox.AddString(str);
    for (UINT i = 1; i < game.playerCount; ++i) {
        str.Format(_T("%u. rival: %u cards, %d points"), i, game.players[i].playerHand.hand.size(), game.scBoard.GetPlayerPoints(i));
        playerListBox.AddString(str);
    }
    playerListBox.SetCurSel(game.currentPlayer);

}

void View::ShowHand(CDC* pDC)
{
    if (!game.getPlayerhand().empty())
    {
        LoadImagesFromResource();
        std::vector<UINT> cardsToEnlarge;
        if (game.drawSum == 0) {
            cardsToEnlarge = game.players[0].playerHand.CheckForAvailableCards(game.playedCards.getLast());
        }
        else {
            cardsToEnlarge = game.players[0].playerHand.CheckForStackingCards(game.playedCards.getLast());
        }
        m_imageRects.clear();

        Graphics graphics(pDC->GetSafeHdc());

        // Define the preview area (for example, top of the client area)
        CRect clientRect;
        GetHandRect(clientRect);

        int xOffset = 0;

        for (int i = 0; i < hand_bitmaps.size(); ++i)
        {
            UINT imageWidth = clientRect.Width() / (hand_bitmaps.size() - cardsToEnlarge.size() + 2 * cardsToEnlarge.size());

            UINT imageHeight = clientRect.Height() - 5;
            Gdiplus::Bitmap* pImage = hand_bitmaps[i];
            if (pImage)
            {
                imageHeight /= 2;
                if (pImage->GetWidth() / 2 < imageWidth) { //prevents cards from taking the entire screen
                    imageWidth = pImage->GetWidth() / 2;
                }
                if (game.currentPlayer == 0) {
                    for (UINT j : cardsToEnlarge)
                    {
                        if (j == i) {
                            imageWidth *= 2;
                            imageHeight = clientRect.Height();
                            if (pImage->GetWidth() < imageWidth) { //prevents cards from taking the entire screen
                                imageWidth = pImage->GetWidth();
                            }
                            break;
                        }
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



void View::ShowWinScreen(int player, const bool rndWin)
{
    RoundWinDlg rwDlg(player,rndWin,nullptr);
    if (rwDlg.DoModal() == IDOK) {

        game.resetGame(rndWin);
        Invalidate();
        UpdateWindow();
        UpdateListBox();
        return;
    }
    else {
        AfxGetMainWnd()->PostMessage(WM_CLOSE);
    }

}

void View::OnTimer(UINT_PTR timerId)
{
    if(game.currentPlayer != 0) {

        if (game.processMove()) {
            KillTimer(timerId);
            ShowWinScreen(game.currentPlayer, game.UpdatePoints());
            UpdateListBox();
            Invalidate();
            UpdateWindow();
            return;
        }
        UpdateListBox();
        Invalidate();
        UpdateWindow();
    }
    else {
        KillTimer(timerId);
    }
    CView::OnTimer(timerId);
}