#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#include<vector>
#include<string.h>
#include"Uno.h"
#include"Game.h"
#include"Card.h"
#include"ChooseColorDlg.h"

#include <future>
#include <chrono>


class View :
    public CView
{
    public:
        Game* game;
        void loadGame(Game* gm);
        virtual void OnDraw(CDC* pDC);  // Override to perform drawing
        View() {};
        ~View();
        DECLARE_DYNCREATE(View)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        CButton DrawButton;
        CButton SkipButton;
        CButton UnoButton;
        bool isUno = false;
        CListBox m_ListBox;
        afx_msg void OnDrawButtonClick();
        afx_msg void OnSkipButtonClick();
        afx_msg void OnUnoButtonClick();
        std::vector<Gdiplus::Bitmap*> hand_bitmaps;
        void OnInitialUpdate();
        std::vector<CRect> m_imageRects;          // Store the position and size of each image
        int m_hoveredImageIndex = -1;



        BOOL LoadImagesFromResource();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);    // Handle mouse hover
        void ShowPreview(CDC* pDC, Gdiplus::Bitmap* pImage);

        
        void ShowPlayedCard(CDC* pDC, const Card card) const;
        void GetPreviewRect(CRect& previewRect) const;
        void UpdateListBox();

        void ShowHand(CDC* pDC);
        void GetHandRect(CRect& previewRect) const;
        BOOL OnEraseBkgnd(CDC* pDC);
        DECLARE_MESSAGE_MAP()

};

