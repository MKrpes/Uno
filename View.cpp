#include "pch.h"
#include "View.h"
#include"Resource.h"


IMPLEMENT_DYNCREATE(View, CView)
BEGIN_MESSAGE_MAP(View, CView)
    ON_WM_CREATE()
    ON_BN_CLICKED(1001, &View::OnDrawButtonClick)
    ON_BN_CLICKED(1002, &View::OnUnoButtonClick)
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

    // Force a redraw to display the loaded image
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
    Invalidate();
    return TRUE;
}

void View::OnMouseMove(UINT nFlags, CPoint point)
{
    bool hoverChanged = false;

    // Check if the mouse is hovering over an image
    for (int i = 0; i < m_imageRects.size(); ++i)
    {
        if (m_imageRects[i].PtInRect(point)) //moguce puno bolje
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

    // If no image is hovered, reset the hover index
    if (!hoverChanged && m_hoveredImageIndex != -1)
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
        CRect(10, 10, 100, 40), this, 1001);

    UnoButton.Create(_T("Uno"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(100, 100, 200, 130), this, 1002);

    return 0;
}
void View::OnDrawButtonClick()
{
    AfxMessageBox(_T("Button clicked!")); //TODO!!!!!!!!!!!!!!!
}
void View::OnUnoButtonClick()
{
    AfxMessageBox(_T("Uno Button clicked!")); //TODO
}

afx_msg void View::OnLButtonDown(UINT nFlags, CPoint point) {

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

        int xOffset = clientRect.right - previewWidth - 20;  // Right side of the window
        int yOffset = 20;  // Top of the window

        // Draw the enlarged preview of the hovered image
        graphics.DrawImage(pImage, xOffset, yOffset, previewWidth, previewHeight);
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

        int previewWidth = 50;   //!!!test!!! change later
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
        //CRect clientRect;
        //GetClientRect(&clientRect);

        // Calculate available area for the images
        int imageHeight = 200;

        int yOffset = clientRect.bottom - imageHeight; // Leave space for image row

        m_imageRects.clear();  // Clear previous rects

        int xOffset = 0;  // Horizontal position to start drawing
        int imageWidth = clientRect.Width() / 10;
        // Draw images side by side, with their actual sizes
        for (int i = 0; i <hand_bitmaps.size(); ++i)
        {
            Gdiplus::Bitmap* pImage = hand_bitmaps[i];
            if (pImage)
            {
                //int imageWidth = pImage->GetWidth();   // Use actual image width
                //int imageHeight = pImage->GetHeight(); // Use actual image height

                // Make sure images don't overlap
                if (i * imageWidth > clientRect.Width()) break;

                // Draw the image at the bottom
                graphics.DrawImage(pImage, xOffset, yOffset, imageWidth, imageHeight);
                 //!!!!!!!!TEST!!!!!!!TEST!!!!!!!!!!!!!!!TESTTEST
                // Store the image's position (for click and hover detection)
                //CRect imageRect(xOffset, yOffset - imageHeight, xOffset + imageWidth, yOffset);
                CRect imageRect(xOffset, yOffset, xOffset + imageWidth, clientRect.bottom);
                m_imageRects.push_back(imageRect);

                // Increment the horizontal offset for the next image
                xOffset += imageWidth;  // Add some padding between images
            }
        }
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

void View::GetPreviewRect(CRect& previewRect) const
{
    // Define the preview area (example: top-right corner)
    CRect clientRect;
    GetClientRect(&clientRect);

    int previewWidth = 500;   // Width of the enlarged preview
    int previewHeight = 200;  // Height of the enlarged preview

    int xOffset = clientRect.right - previewWidth;  // Place on the right
    int yOffset = 20;  // Top of the window

    // Set the calculated preview rectangle
    previewRect = CRect(xOffset, yOffset, xOffset + previewWidth, yOffset + previewHeight);
}

BOOL View::OnEraseBkgnd(CDC* pDC)
{
    // Prevents background from being erased to reduce flickering
    return TRUE;
}