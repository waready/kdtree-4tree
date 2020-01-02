#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
HINSTANCE hInst;
class Punto
{   public:
    int x,y;
    Punto(int xx=0,int yy=0)
    {   x=xx;
        y=yy;
    }
};
class Nodo
{   public:
    Punto P;
    int eje;
    Nodo *Izq, *Der;
    Nodo(Punto PP,int e,Nodo *Iz=NULL,Nodo *De=NULL)
    {   P=PP;
        eje=e;
        Izq=Iz;
        Der=De;
    }
};
class kdtree2d
{   public:
    Nodo *Raiz;
    kdtree2d()
    {   Raiz=NULL;
    }
    void Insertar(Punto PP)
    {   Ins(PP,Raiz,0);
    }
    void Ins(Punto PP,Nodo *&R,int e)
    {   if(R==NULL)
            R=new Nodo(PP,e);
        else
        {   if(R->eje==0)
            {   if(PP.x<R->P.x)
                    Ins(PP,R->Izq,1);
                else
                    Ins(PP,R->Der,1);
            }
            else
            {   if(PP.y<R->P.y)
                    Ins(PP,R->Izq,0);
                else
                    Ins(PP,R->Der,0);
            }
        }
    }
    void Mostrar(HDC hdc,int x,int y,int a)
    {   Mos(Raiz,hdc,x,y,a);
    }
    void Mos(Nodo *R,HDC hdc,int x,int y,int a)
    {   if(R!=NULL)
        {   char Cad[10];
            sprintf(Cad,"%i",R->P.x);
            TextOut(hdc,x,y,Cad,strlen(Cad));
            sprintf(Cad,"%i",R->P.y);
            TextOut(hdc,x,y+15,Cad,strlen(Cad));
            sprintf(Cad,"%i",R->eje);
            TextOut(hdc,x,y+30,Cad,strlen(Cad));
            Mos(R->Izq,hdc,x-a,y+50,a/2);
            Mos(R->Der,hdc,x+a,y+50,a/2);
        }
    }
    void MostrarR(HDC hdc,int xi,int yi,int xf,int yf)
    {   MosR(Raiz,hdc,xi,yi,xf,yf);
    }
    void MosR(Nodo *R,HDC hdc,int xi,int yi,int xf,int yf)
    {   if(R!=NULL)
        {   int xx=R->P.x;
            int yy=R->P.y;
            if(R->eje==0)
            {   MoveToEx(hdc,xx,yi,NULL);
                LineTo(hdc,xx,yf);
                MosR(R->Izq,hdc,xi,yi,xx,yf);
                MosR(R->Der,hdc,xx,yi,xf,yf);
            }
            else
            {   MoveToEx(hdc,xi,yy,NULL);
                LineTo(hdc,xf,yy);
                MosR(R->Izq,hdc,xi,yi,xf,yy);
                MosR(R->Der,hdc,xi,yy,xf,yf);
            }
            Ellipse(hdc,xx-2,yy-2,xx+2,yy+2);
        }
    }
};
int pxi,pyi,pxf,pyf;
kdtree2d Q;
BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{   switch(uMsg)
    {   case WM_PAINT:
        {   PAINTSTRUCT ps;
            HDC hdc;
            hdc=BeginPaint(hwndDlg,&ps);
            Q.Mostrar(hdc,550,50,120);
            Rectangle(hdc,pxi,pyi,pxf,pyf);
            Q.MostrarR(hdc,pxi,pyi,pxf,pyf);
            EndPaint(hwndDlg,&ps);
        }
        return TRUE;
        case WM_LBUTTONDOWN:
        {   long xPos = GET_X_LPARAM(lParam);
            long yPos = GET_Y_LPARAM(lParam);
            if(xPos<pxf&&xPos>pxi&&yPos<pyf&&yPos>pyi)
                Q.Insertar(Punto(xPos,yPos));
            InvalidateRect(hwndDlg,NULL,true);
        }
        return TRUE;
        case WM_MOUSEMOVE:
        {   long xPos = GET_X_LPARAM(lParam);
            long yPos = GET_Y_LPARAM(lParam);
            SetDlgItemInt(hwndDlg,EDITX,(int)xPos,FALSE);
            SetDlgItemInt(hwndDlg,EDITY,(int)yPos,FALSE);
        }
        return TRUE;
        case WM_INITDIALOG:
        {   pxi=10,pyi=50,pxf=210,pyf=250;
        }
        return TRUE;
        case WM_CLOSE:
        {   EndDialog(hwndDlg, 0);
        }
        return TRUE;
        case WM_COMMAND:
        {   switch(LOWORD(wParam))
            {
            }
        }
        return TRUE;
    }
    return FALSE;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
