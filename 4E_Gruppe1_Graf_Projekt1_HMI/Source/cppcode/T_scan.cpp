#include "T_IPC.H"
#include "T_NUC.H"  

void _ScanBar::Init(void)
{
  Ptr = NULL;
  No  = 0;
  Pos = 0;
}

void _ScanBar::Free(void)
{
  _UWORD i;

  for(i=0; i<No; i++)
    free_SCAN(&Ptr[i]);

  Memory2((void**)&Ptr, 0);
  Init();
}

void _ScanBar::SetPos(_UWORD no)
{
  Pos = no;
}

_UWORD _ScanBar::Add(const _ASCII *txt, _DWORD max)
{
  _DWORD size;
  _UWORD retcode = 0xFFFF;
  _KOORD y, xx;
  _SCAN  *p;
  _COLOR col1, col2;
  _ROOM  sroom;

  size = (No+1) * sizeof(_SCAN);

  PushMemColor(MEMORY_PRG);
  if(Memory2((void**)&Ptr, size) != 0)
  {
    GetScreenSize(&sroom);

    p = &Ptr[No];
    init_SCAN(p);
    y = (Pos+2) * 12;
    p->max        = max;
    p->room.xy1.x = 10;
    p->room.xy1.y = y;
    p->room.xy2.x = sroom.xy2.x-20;
    p->room.xy2.y = y + 8;
    retcode = No;
    Pos ++;
    No  ++;
    Font.Set(DEFFONT, NULL);
    OutTextXY(10, y, (void*)txt, T_COPY|T_SOLID|T_PROP, MakeColor_Makro(BLACK, LIGHTGRAY), sizeof(_ASCII));
   #ifdef UC_ROTATE
    RefreshRectangle(&p->room);
   #endif
    xx = StrWidth((void*)txt, sizeof(_ASCII)) + 14;
    if((xx > p->room.xy1.x)&&(xx < p->room.xy2.x))
      p->room.xy1.x = xx;

    if(max != 0)
    {
      col1 = MakeColor_Makro(BLACK, BLACK);
      col2 = MakeColor_Makro(WHITE, DARKGRAY);
      DrawButton(&p->room, T_COPY|T_SOLID, _3DFRAME, col1, col2);
//      Button(p->room.xy1.x-1,p->room.xy1.y-1, p->room.xy2.x+1,p->room.xy2.y+1, T_COPY|T_SOLID, col1, col2);
    }
  }
  PopMemColor();

 #ifdef UC_ROTATE
  RefreshRectangle(&p->room);
 #endif

  return(retcode);
}

void _ScanBar::Run(_UWORD i, _DWORD akt)
{
  _SCAN *p;
  _KOORD x;

  if(i < No)
  {
    p = &Ptr[i];
    if(akt == 0)
      x = 0;
    else if(akt == p->max)
      x = p->room.xy2.x - p->room.xy1.x;
    else
      x = ((akt*(p->room.xy2.x - p->room.xy1.x))/p->max);

    if(x != p->oldx)
    {
      //Bar(p->room.xy1.x+1, p->room.xy1.y+1, p->room.xy1.x+x, p->room.xy2.y-1, T_SOLID|T_COPY, MakeColor_Makro(BLACK, LIGHTGRAY));
      Bar(p->room.xy1.x+1, p->room.xy1.y+1, p->room.xy1.x+x, p->room.xy2.y-1, T_SOLID|T_COPY, p->color);
      
      p->oldx = x;
     #ifdef UC_ROTATE
      RefreshRectangle(&p->room);
     #endif

    }
  }
}

void _ScanBar::Reset(_UWORD i, _DWORD max, _BOOL changecolor)
{
  _SCAN *p;

  if(i < No)
  {
    p = &Ptr[i];
    p->oldx = 0;
    p->max  = max;
   
    _UWORD col = (changecolor == _TRUE)? LIGHTGREEN : LIGHTGRAY;
   #ifdef UC_GRAYSCALE
    transform_color_to_gray(&col);
   #endif
    p->color = MakeColor_Makro(BLACK, col);
   
    Bar(p->room.xy1.x+1, p->room.xy1.y+1, p->room.xy2.x-1, p->room.xy2.y-1, T_SOLID|T_COPY, MakeColor_Makro(BLACK, BLACK));
   #ifdef UC_ROTATE
    RefreshRectangle(&p->room);
   #endif
  }
}

void _ScanBar::End(_UWORD i)
{
  if(i<No)
  {
    Run(i, Ptr[i].max);
    if((i+1) == No)
    {
      free_SCAN(&Ptr[i]);
      No --;
      PushMemColor(MEMORY_PRG);
      Memory2((void**)&Ptr, No*sizeof(_SCAN));
      PopMemColor();
    }
  }
}

//****************************************************************************
//  LASAL Interface
//****************************************************************************
//****************************************************************************
//****************************************************************************

extern "C" _UWORD ScanBar_Add(_ASCII *txt, _DWORD max)
{
  return(ScanBar.Add(txt, max));
}

extern "C" void   ScanBar_Run(_UWORD handle, _DWORD act)
{
  ScanBar.Run(handle, act);
}

extern "C" void   ScanBar_End(_UWORD handle)
{
  ScanBar.End(handle);
}
