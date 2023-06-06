#include "T_IPC.H"
#include "T_NUC.H"

#define SCROLL_OUTTIMER                  // timedelay to draw page after scroll by hid
#define SCROLL_LASTLINE                  // display lastline (bottom-halfline) of page
#define SCROLL_LEVEL_INACTIVE_COLOR MakeColor_Makro(LIGHTGRAY, LIGHTGRAY)

#ifdef USER_DEMAG
 #define LEVELBUTTON_TOP1      _UP
 #define LEVELBUTTON_TOP2      _PGUP
 #define LEVELBUTTON_BOTTOM2   _PGDOWN
 #define LEVELBUTTON_BOTTOM1   _DOWN
#else
                                         // +--+
 #define LEVELBUTTON_TOP1      _PGUP     // |  |
                                         // +--+
 #define LEVELBUTTON_TOP2      _UP       // |  |
                                         // +--+
                                         // |  |
                                         // |  |
                                         // |  |
                                         // |  |
                                         // +--+
 #define LEVELBUTTON_BOTTOM2   _DOWN     // |  |
                                         // +--+
 #define LEVELBUTTON_BOTTOM1   _PGDOWN   // |  |
                                         // +--+
#endif

//#define ENTER_ON_NEGEDGE

void   Start_SCROLL(_SCROLL*, _BOOL);
void   Ready_SCROLL(_SCROLL*, _BOOL);
void   Run_SCROLL(_SCROLL*, _EVENT*);
void   End_SCROLL(_SCROLL*);
void   GetLinePosition_SCROLL(_SCROLL*, _UDWORD, _ROOM*);
void   OutLine_SCROLL(_SCROLL*, _UDWORD, _UDWORD, _BOOL, _BOOL);
void   ActBeam_SCROLL(_SCROLL*, _BOOL);
void   Beam_SCROLL(_SCROLL*, _UDWORD, _UDWORD, _BOOL);
void   OutPageBeam_SCROLL(_SCROLL*, _UDWORD);
void   OutPage_SCROLL(_SCROLL*);
void   Draw_SCROLL(_SCROLL*, _BOOL);
void   ScrollUp_SCROLL(_SCROLL*);
void   ScrollDown_SCROLL(_SCROLL*);
_UWORD GetPosition_SCROLL(_SCROLL*);


_UWORD calculate_pageheight(_POSITION *pos, _ROOM *pr, _UBYTE fromwhere)
{
  _UBYTE  *pl;
  _UDWORD y, yy;
  _UDWORD height = 0;
  _UDWORD i;
  _UDWORD no;


  y = (pr->xy2.y - pr->xy1.y + 1);
  yy = 0;

  if(fromwhere == 0xFF)
  {
    pos->totalheight = 0;
    pl = pos->lineheight;
    for(i=0; i<pos->no; i++)
    {
      pos->totalheight += *pl;
      pl ++;
    }

    calculate_pageheight(pos, pr, 0);
  }
  else if(fromwhere == 0)  // von oben nach unten
  {
    pl = &pos->lineheight[pos->begin];
    no = pos->no - pos->begin;
    while(no > 0)
    {
      yy += *pl;
      if(yy <= y)
        height++;
      else
        break;

      pl++;
      no--;
    }

    pos->height = height;
    if(pos->height <= pos->pos - pos->begin)
    {
      pos->begin++;
      calculate_pageheight(pos, pr, 0);
    }

  }
  else if(fromwhere == 1)  // von unten nach oben - Cursor an letzter Zeile - _DOWN
  {
    pl = &pos->lineheight[pos->pos];
    no = pos->pos;
    while(no > 0)
    {
      yy += *pl;
      if(yy <= y)
        height++;
      else
        break;

      pl--;
      no--;
    }

  }
  else if(fromwhere == 2) // von oben nach oben - _PGUP
  {
    pl = &pos->lineheight[pos->begin-1];
    no = pos->begin;
    while(no > 0)
    {
      yy += *pl;
      if(yy <= y)
        height++;
      else
        break;

      pl--;
      no--;
    }
  }

  return(height);
}

_UDWORD get_line_no(_POSITION *pos, _ROOM *pr, _DOT *pdot)
{
  _UDWORD line = 0xFFFFFFFF;
  _UBYTE *pl;
  _UDWORD yy, no, ypos;


  if((pdot->x >= pr->xy1.x) && (pdot->x <= pr->xy2.x) && (pdot->y >= pr->xy1.y) && (pdot->y <= pr->xy2.y))
  {
    pl = &pos->lineheight[pos->begin];
    ypos = pdot->y - pr->xy1.y;
    no = 0;
    yy = 0;
    line = 0;

    while(no < pos->height)
    {
      yy += *pl;
      if(yy < ypos)
        line++;
      else
        break;

      pl++;
      no++;
    }


  }

  return(line);
}

_UDWORD get_line_no(_POSITION *pos, _UDWORD y)
{
  _UDWORD line = 0;
  _UBYTE *pl;
  _UDWORD yy;
  _UDWORD i;


  pl = pos->lineheight;
  yy = 0;

  for(i=0; i<pos->totalheight; i++)
  {
    yy += *pl;
    if(yy < y)
      line++;
    else
      break;

    pl++;
  }

  return(line);
}

_POSRESULT calculate_v_position(_POSITION *pos, _EVENT *pe, _ROOM *pr)
{
  _POSRESULT retcode = P_NOP;
  _UDWORD height, line;

  if((pe != NULL) && (pos != NULL))
  {
    if(pos->no > 0)
    {
      if(pe->ftype == _EVENT_KEYPRESS)
      {
        switch(pe->scancode)
        {
          case _UP:
            if(pos->pos > 0)
            {
//              retcode = P_CURSOR;
              retcode = P_REDRAW;
              pos->oldpos = pos->pos;
              pos->pos--;
              if(pos->pos < pos->begin)
              {
//                retcode = P_SCROLLUP;
                retcode = P_REDRAW;
                pos->oldbegin = pos->begin;
                pos->begin--;
                calculate_pageheight(pos, pr, 0);
              }
            }
            break;

          case _DOWN:
            if(pos->pos < pos->no - 1)
            {
//              retcode = P_CURSOR;
              retcode = P_REDRAW;
              pos->oldpos = pos->pos;
              pos->pos++;
              if(pos->pos >= pos->height + pos->begin)
              {
//                retcode = P_SCROLLDOWN;
                retcode = P_REDRAW;
                height = calculate_pageheight(pos, pr, 1);
                pos->oldbegin = pos->begin;
                pos->begin = pos->pos - height;
              }
              calculate_pageheight(pos, pr, 0);
            }
            break;

				  case _PGUP:
            if(pos->pos > 0)
            {
              retcode = P_REDRAW;
              pos->oldpos = pos->pos;
              pos->oldbegin = pos->begin;

              height = calculate_pageheight(pos, pr, 2);

              if(height == 0)
              {
                pos->pos = 0;
                pos->begin = 0;
              }
              else if(pos->pos - height >= 0)
              {
                pos->pos -= height;
                pos->begin -= height;
//                pos->pos = pos->begin + height;
              }

              calculate_pageheight(pos, pr, 0);
            }
            break;

          case _PGDOWN:
            if(pos->pos < pos->no - 1)
            {
              retcode = P_REDRAW;
              pos->oldpos = pos->pos;
              pos->oldbegin = pos->begin;

              if(pos->pos + pos->height < pos->no)
              {
                pos->pos += pos->height;
                pos->begin += pos->height;
              }
              else
              {
                pos->pos = pos->no - 1;
              }

              calculate_pageheight(pos, pr, 0);

            }
            break;

          case _ENTER:
            line = get_line_no(pos, pr, &pe->dot);
            if(line != 0xFFFF)
            {
              retcode = P_REDRAW;
              pos->oldpos = pos->pos;
              pos->pos = pos->begin + line;
              if(line >= pos->height)
              {
                pos->oldbegin = pos->begin;
                pos->begin ++;
              }

              calculate_pageheight(pos, pr, 0);
            }
            break;

        }
      }

      else if((pe->ftype == _EVENT_HIDMOVE) || (pe->ftype == _EVENT_SHUTTLEINC) || (pe->ftype == _EVENT_SHUTTLEDEC))
      {
        if(pe->ftype == _EVENT_SHUTTLEINC)
          pos->pos += pe->scancode;
        else if(pe->ftype == _EVENT_SHUTTLEDEC)
          pos->pos -= pe->scancode;

        if(pos->pos >= pos->no)
          pos->pos = pos->no - 1;
        else if(pos->pos < 0)
          pos->pos = 0;

        if(pos->pos != pos->oldpos)
        {
          pos->oldpos = pos->pos;

          if(pos->pos > pos->oldpos)
          {
            if(pos->pos > (pos->begin + pos->height - 1))
            {
              pos->oldbegin = pos->begin;
              pos->begin += pos->height - 1;
            }
          }
          else
          {
            if(pos->pos < pos->begin)
            {
              pos->oldbegin = pos->begin;
              pos->begin = pos->pos;
            }
              
          }
          retcode = P_REDRAW;
          calculate_pageheight(pos, pr, 0);
        }
      }

    }
  }

  return(retcode);
}

void OutPage_SCROLL(_SCROLL *p)
{
  OutPageBeam_SCROLL(p, 0xFFFF);
}

void GetLinePosition_SCROLL(_SCROLL *p, _UDWORD y, _ROOM *pr)
{
  _UBYTE *ptr;
  _UDWORD i;
  _UDWORD yy;

  pr->xy1.x = p->scroll_room.xy1.x;
  pr->xy2.x = p->scroll_room.xy2.x;

  if(p->position.lineheight == NULL)
  {
    pr->xy1.y = p->scroll_room.xy1.y + y * p->line_height;
    pr->xy2.y = pr->xy1.y + p->line_height - 1;
  }

  else
  {
    ptr = &p->position.lineheight[p->position.begin];
    yy = 0;
    for(i=0; i<y; i++, ptr++)
    {
      yy += *ptr;
    }
    pr->xy1.y = p->scroll_room.xy1.y + yy;
    pr->xy2.y = pr->xy1.y + *ptr - 1;
    if(pr->xy2.y > p->scroll_room.xy2.y)
      pr->xy2.y = p->scroll_room.xy2.y;
  }

}

void OutLine_SCROLL_sub(_SCROLL *p, _UDWORD y, _UDWORD no, _BOOL st, _BOOL redraw_background, _BOOL do_refresh)
{
  _ROOM   r;
  _REGION scrreg, actreg, ioreg=NULL, newreg=NULL;
  _ASCII  txt[30];
  _COLOR  colframe, coltxt, colback, color;
  _ATTRIB attrib;
  _FRAMETYPE frametype = _DEFFRAME;

  if(p->position.no == 0)  // no lines? --> no active beam
    st = _FALSE;

  attrib = (st == _TRUE)? p->attrib_activ : p->attrib_inactiv;
  Font.Set(p->font, &attrib);
  GetLinePosition_SCROLL(p, y, &r);

  actreg = ActivateAndRegion(&ioreg, &newreg, &r);
  if(p->position.lineheight != NULL)
    scrreg = ActivateAndRegion(&ioreg, &newreg, &p->scroll_room);

 #ifdef UC_ROTATE
  _ROOM refroom = r;
 #endif
 #ifdef UC_MOUSE
  _UWORD hide = IfNecHideMouseCursor(&r);
 #endif

  color = (st == _TRUE)? p->color_activ : p->color_inactiv;

  Cursor_Hide(p->Cursor);

  if(redraw_background == _TRUE)
  {
    if(p->pt_draw != NULL)
    {
      p->pt_draw(p);
    }
    else
    {
      color = InvertColor_Makro(color);
      if(is_invisible(color, T_COPY|T_SOLID) == _FALSE)
      {
        if(p->frametype < _THEMEFRAME)
        {
          Bar(r.xy1.x, r.xy1.y, r.xy2.x, r.xy2.y, T_COPY|T_SOLID, color);
        }
        else
        {
          color = MakeColor_Makro(color, color);
          DrawButton(&p->out_room, T_FILL|T_COPY|T_SOLID| ((attrib & T_INVERTTHEME)? T_INVRS:0), p->frametype, color, p->frame_out);
        }
      }
    }
  }

  r.xy1.x -= p->hposition.begin;

  if(p->pt_line != NULL) 
  {
    p->pt_line(p, p->pt, &r, no, st);
  }
  else
  {
    color = MakeColor_Makro(INVISIBLE, GetPenColor_Makro(color));
    StrCpy(txt, sizeof(_ASCII), "line ", sizeof(_ASCII));
    DToA(&txt[5], no, 0x0105, sizeof(_ASCII));

    coltxt   = MakeColor_Makro(INVISIBLE, color);
    colback  = MakeColor_Makro(GetBackColor_Makro(color), GetBackColor_Makro(color));
    colframe = MakeColor_Makro(INVISIBLE, INVISIBLE);

    OutTextAlign(txt, 0, &r, p->font, attrib, frametype, coltxt, colback, colframe, sizeof(_ASCII));
  }

 #ifdef UC_ROTATE
  if(do_refresh == _TRUE)
    RefreshRectangle(&refroom);
 #endif
 #ifdef UC_MOUSE
  IfNecShowMouseCursor(hide);
 #endif

  if(p->position.lineheight != NULL)
    DeactivateAndRegion(scrreg, &ioreg, &newreg);

  DeactivateAndRegion(actreg, &ioreg, &newreg);
}

void ActBeam_SCROLL(_SCROLL *p, _BOOL st)
{
  Beam_SCROLL(p, p->position.pos-p->position.begin, p->position.pos, st);
}

void Beam_SCROLL_sub(_SCROLL *p, _UDWORD y, _UDWORD no, _BOOL st, _BOOL do_refresh)
{
  Cursor_End(p->Cursor);
  if(p->pt_beam != NULL)
    p->pt_beam(p, p->pt, y, no, st);
  else
    OutLine_SCROLL_sub(p, y, no, st, (p->noclrscr == _TRUE) ? _FALSE : _TRUE, do_refresh);

  if((p->Cursor != NULL)&&(st == _TRUE))
    set_MENCURSOR(&p->mencursor);

//  if((DrawBackGround == 0)&&(p->CursorBlink == _TRUE))
//  {
//    p->CursorDelayActive = _TRUE;
//    p->CursorDelayTimer  = get_abstime();
//  }
}

void OutDraw_SCROLL_sub(_SCROLL *p, _BOOL do_refresh)
{
  _ROOM  room;
  _COLOR color;

  room = p->out_room;

 #ifdef UC_MOUSE
  HideMouseCursor();
 #endif

  if(p->pt_draw != NULL)
  {
    p->pt_draw(p);
  }
  else
  {
    if((p->noclrscr == _TRUE)&&(p->frametype < _THEMEFRAME))
      color = MakeColor_Makro(INVISIBLE, INVISIBLE);
    else
      color = MakeColor_Makro(GetBackColor_Makro(p->color_inactiv), GetBackColor_Makro(p->color_inactiv));

    if(p->frametype < _THEMEFRAME)
    {
      DrawButton(&room, T_FILL|T_COPY|T_SOLID, p->frametype, color, p->frame_out);
      if(p->frame_scroll != DEFCOLOR)
      {
        room.xy1.x = p->scroll_room.xy1.x - 1;
        room.xy1.y = p->scroll_room.xy1.y - 1;
        room.xy2.x = p->scroll_room.xy2.x + 1;
        room.xy2.y = p->scroll_room.xy2.y + 1;
        DrawButton(&room, T_COPY|T_SOLID, p->frametype, INVISIBLE, p->frame_scroll);
      }
    }
    else
    {
      DrawButton(&room, T_FILL|T_COPY|T_SOLID|((p->attrib_activ & T_INVERTTHEME)? T_INVRS:0), p->frametype, color, p->frame_out);
    }
  }

//  level_draw(&p->level, _FALSE);
//  level_run(&p->level, p->position.no, p->position.pos, _FALSE);

 #ifdef UC_ROTATE
  if(do_refresh == _TRUE)
    RefreshRectangle(&room);
 #endif
 #ifdef UC_MOUSE
  ShowMouseCursor();
 #endif
}

void OutPageBeam_SCROLL(_SCROLL *p, _UDWORD actpos)
{
  _UDWORD i, j;
  _REGION actreg, ioreg=NULL, newreg=NULL;
  _ROOM   room, r;

  Cursor_End(p->Cursor);

  GetLinePosition_SCROLL(p, 0, &r);
  room.xy1 = r.xy1;
  GetLinePosition_SCROLL(p, p->position.height-1, &r);
  room.xy2 = r.xy2;

 #ifdef UC_MOUSE
  _UWORD hide = IfNecHideMouseCursor(&room);
 #endif

  if(p->noclrscr == _FALSE)
  {
   #ifndef SCROLL_LASTLINE
    if(p->position.lineheight == NULL)
      actreg = ActivateAndRegion(&ioreg, &newreg, &room);
    else
   #endif
      actreg = ActivateAndRegion(&ioreg, &newreg, &p->scroll_room);

    OutDraw_SCROLL_sub(p, _FALSE);
    p->nobck = true;
    DeactivateAndRegion(actreg, &ioreg, &newreg);
  }

//  j = actpos - p->position.begin;
//  if(j < p->position.height)
//    Beam_SCROLL(p, j, actpos, _TRUE);

  j = p->position.begin;
  for(i=0; i<p->position.height; i++, j++)
  {
    if(j != actpos)
      OutLine_SCROLL_sub(p, i, j, _FALSE, _FALSE, _FALSE);
    else
      Beam_SCROLL_sub(p, i, actpos, _TRUE, _FALSE);
  }

 #ifdef SCROLL_LASTLINE
  if((p->scroll_room.xy1.y + p->position.height * p->line_height) < p->scroll_room.xy2.y)
  {
    actreg = ActivateAndRegion(&ioreg, &newreg, &p->scroll_room);
    OutLine_SCROLL_sub(p, i, j, _FALSE, _FALSE, _FALSE);
    DeactivateAndRegion(actreg, &ioreg, &newreg);
  }
 #endif

  p->nobck = false;

  if(p->position.lineheight != NULL)
  {
    if(j < p->position.no)
      OutLine_SCROLL_sub(p, i, j, _FALSE, _FALSE, _FALSE);
  }

 #ifdef UC_ROTATE
  RefreshRectangle(&p->out_room);
 #endif
 #ifdef UC_MOUSE
  IfNecShowMouseCursor(hide);
 #endif
}

void Draw_SCROLL(_SCROLL *p, _BOOL beam)
{
 #ifdef UC_MOUSE
  HideMouseCursor();
 #endif

 #ifdef USER_BILLION
  if(p->position.no < p->position.height)
    p->level.color = SCROLL_LEVEL_INACTIVE_COLOR;
  else
    p->level.color = MakeColor_Makro(GetBackColor_Makro(p->color_inactiv), GetBackColor_Makro(p->color_inactiv));
 #endif

  OutDraw_SCROLL_sub(p, _FALSE);
  level_draw(&p->level, _FALSE, _TRUE, p->image, p->frametype); //(DrawBackGround == 0)? _TRUE : _FALSE);
  level_run(&p->level, p->position.no, p->position.pos, _FALSE, p->image, p->frametype);
  level_draw(&p->hlevel, _TRUE, _TRUE, p->image, p->frametype); //(DrawBackGround == 0)? _TRUE : _FALSE);
  level_run(&p->hlevel, p->hposition.no, p->hposition.pos, _TRUE, p->image, p->frametype);
  OutPageBeam_SCROLL(p, (beam == _TRUE)? p->position.pos : 0xFFFFFFFF);

 #ifdef UC_MOUSE
  ShowMouseCursor();
 #endif

 #ifdef UC_ROTATE
  RefreshRectangle(&p->out_room);
 #endif

}

void Run_SCROLL(_SCROLL *p, _EVENT *pe)
{
  _UDWORD    oldpos   = p->position.oldpos;
  _UDWORD    oldbegin = p->position.oldbegin;
  _POSRESULT st;
  _ROOM      room;
  _COLOR     col;

  if(p->Cursor != NULL)
  {
    if(ask_MENCURSOR(&p->mencursor) == _TRUE)
    {
      GetLinePosition_SCROLL(p, p->position.pos - p->position.begin, &room);
      room.xy1.x += p->cursor_dx1;
      room.xy2.x += p->cursor_dx2;
      room.xy1.y += p->cursor_dy1;
      room.xy2.y += p->cursor_dy2;
      col = ((p->flash_cursorcolor) == INVISIBLE)? SetUp.GetEditColorCursor(_EDITACTIVE) : p->flash_cursorcolor;
      Cursor_Set(p->Cursor, &room, col, 0);
    }
  }

  if(pe != NULL)
  {
   #ifdef HID
    #ifdef SCROLL_OUTTIMER
    _BOOL  timedelay = (pe->ftype == _EVENT_HIDMOVE)? _TRUE : _FALSE;
    #endif
    _UWORD columnwidth = p->scroll_room.xy2.x - p->scroll_room.xy1.x;
    do_HID_SCROLL(pe, &p->level, &p->position, &p->hlevel, &p->hposition, &p->scroll_room, p->line_height, columnwidth);
   #endif

    if(p->position.no > 0)
    {
      if(p->position.lineheight == NULL)
      {
        st = calculate_position(&p->position, &p->hposition, pe, &p->scroll_room);
      }
      else
      {
        st = calculate_v_position(&p->position, pe, &p->scroll_room);
        if(st == P_NOP)
          st = calculate_position(NULL, &p->hposition, pe, &p->scroll_room);
      }

      if(st != P_NOP)
      {
       #ifdef UC_HICOLOR
        switch(st)
        {
          case P_SCROLLUP   :
          case P_SCROLLDOWN :
          case P_SCROLLLEFT :
          case P_SCROLLRIGHT:
          case P_REDRAW     :
                             #ifdef HID
                             #ifdef SCROLL_OUTTIMER
                              if(timedelay == _TRUE)
                              {
                                if(p->do_out_timer == 0)
                                p->do_out_timer = get_abstime();
                              }
                              else
                             #endif
                             #endif
                              {
                                p->do_out_timer = 0;
                                OutPageBeam_SCROLL(p, p->position.pos);
                              }
                              break;
          default           : Beam_SCROLL_sub(p, oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                              Beam_SCROLL_sub(p, p->position.pos - p->position.begin, p->position.pos, _TRUE, _TRUE); // on
                              break;
        }
       #else
        switch(st)
        {
				  case P_SCROLLUP   : Beam_SCROLL_sub(p, oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                              ScrollUp_SCROLL(p);
                              Beam_SCROLL_sub(p, p->position.pos - p->position.begin, p->position.pos, _TRUE, _TRUE); // on
                              break;
				  case P_SCROLLDOWN : Beam_SCROLL_sub(p, oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                              ScrollDown_SCROLL(p);
                              Beam_SCROLL_sub(p, p->position.pos - p->position.begin, p->position.pos, _TRUE, _TRUE); // on
                              break;
				  case P_REDRAW     : OutPageBeam_SCROLL(p, p->position.pos);
                              break;
          default           : Beam_SCROLL_sub(p, oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                              Beam_SCROLL_sub(p, p->position.pos - p->position.begin, p->position.pos, _TRUE, _TRUE); // on
                              break;
        }
       #endif
      }
    }
    
    level_run(&p->level, p->position.no, p->position.pos, _FALSE, p->image, p->frametype);
    level_run(&p->hlevel, p->hposition.no, p->hposition.pos, _TRUE, p->image, p->frametype);

    if(p->pt_run != NULL)
      p->pt_run(p, pe);
  }

/*
 #ifdef USER_BILLION
  _COLOR tmpcol = MakeColor_Makro(GetBackColor_Makro(p->color_inactiv), GetBackColor_Makro(p->color_inactiv));
  if(p->position.no < p->position.height)
    tmpcol = SCROLL_LEVEL_INACTIVE_COLOR;
  if(p->level.color != tmpcol)
  {
    p->level.color = tmpcol;
    level_draw(&p->level, _FALSE, _TRUE, p->image, p->frametype);
  }

  level_run(&p->level, p->position.no, p->position.pos, _FALSE, p->image, p->frametype);
  level_run(&p->hlevel, p->hposition.no, p->hposition.pos, _TRUE, p->image, p->frametype);
 #endif
*/

 #ifdef HID
 #ifdef SCROLL_OUTTIMER
  if(p->do_out_timer != 0)
  {
    if(timediff(p->do_out_timer) > 150) // 70
    {
      p->do_out_timer = 0;
      OutPageBeam_SCROLL(p, p->position.pos);
    }
  }
 #endif
 #endif
}

void ScrollUp_SCROLL(_SCROLL *p)
{
  _ROOM  tmp, room;
  _KOORD h;
  _COLOR color;

  GetLinePosition_SCROLL(p, 0, &tmp);
  h           = (tmp.xy2.y - tmp.xy1.y) + 1;
  GetLinePosition_SCROLL(p, p->position.height-1, &room);
  room.xy1    = tmp.xy1;
  room.xy1.y += h;

  color = MakeColor_Makro(GetBackColor_Makro(p->color_inactiv), GetBackColor_Makro(p->color_inactiv));
 #ifdef UC_MOUSE
  HideMouseCursor();
 #endif
  Scroll(room.xy1.x, room.xy1.y, room.xy2.x+1, room.xy2.y+1, 0, -h, color);

 #ifdef UC_ROTATE
  RefreshRectangle(&room);
 #endif

 #ifdef UC_MOUSE
  ShowMouseCursor();
 #endif
}

void ScrollDown_SCROLL(_SCROLL *p)
{
  _ROOM  tmp, room;
  _KOORD h;
  _COLOR color;

  GetLinePosition_SCROLL(p, 0, &tmp);
  h           = (tmp.xy2.y - tmp.xy1.y);
  GetLinePosition_SCROLL(p, p->position.height-1, &room);
  room.xy1    = tmp.xy1;
  room.xy2.y -= h;
 	color = MakeColor_Makro(GetBackColor_Makro(p->color_inactiv), GetBackColor_Makro(p->color_inactiv));
 #ifdef UC_MOUSE
 	HideMouseCursor();
 #endif
 	Scroll(room.xy1.x, room.xy1.y, room.xy2.x+1, room.xy2.y, 0, h+1 ,color);

 #ifdef UC_ROTATE
  RefreshRectangle(&room);
 #endif

 #ifdef UC_MOUSE
 	ShowMouseCursor();
 #endif
}

_UWORD GetPosition_SCROLL(_SCROLL *p)
{
	return(p->position.pos);
}

void Start_SCROLL(_SCROLL *p, _BOOL firsttime)
{
	if(p->pt_start != NULL)
		p->pt_start(p, firsttime);
}

void Ready_SCROLL(_SCROLL *p, _BOOL firsttime)
{
	Draw_SCROLL(p, _TRUE);

	if(p->pt_ready != NULL)
		p->pt_ready(p, firsttime);
}

void End_SCROLL(_SCROLL *p)
{
	if(p->pt_end != NULL)
		p->pt_end(p);
}

void level_triangle(_ROOM *pr, _UWORD dir, _COLOR color)
{
	_UWORD xx, yy;
	_DOT   dot[3];

 if(GetPenColor_Makro(color) != INVISIBLE)
 {
  if((dir == _UP) || (dir == _DOWN))
  {
    xx = (pr->xy2.x - pr->xy1.x + 1);

    if(xx > 9)
    {
// UC_LEVEL_PGUPPGDOWN begin
      _ROOM room = *pr;
      _DWORD dx, dy, x, y;

      dx = ((room.xy2.x - room.xy1.x + 3)*2) / 4;
      dy = ((room.xy2.y - room.xy1.y + 3)*2) / 5;
      dx = (pr->xy2.x - pr->xy1.x + 1 - dx) / 2;
      dy = (pr->xy2.y - pr->xy1.y + 1 - dy) / 2;

      room.xy1.x += dx;
      room.xy2.x -= dx;
      room.xy1.y += dy;
      room.xy2.y -= dy;

      dx = (room.xy2.x - room.xy1.x + 1) * 5;
      dy = (room.xy2.y - room.xy1.y + 1);

      if(dir == _UP)
      {
        for(y=0; y<dy; y++)
        {
          x = (((y * dx) / dy) + 5) / 10;
          Line(room.xy1.x+x, room.xy2.y-y, room.xy2.x-x, room.xy2.y-y, T_COPY|T_SOLID, color);
        }
      }
      else
      {
        for(y=0; y<dy; y++)
        {
          x = (((y * dx) / dy) + 5) / 10;
          Line(room.xy1.x+x, room.xy1.y+y, room.xy2.x-x, room.xy1.y+y, T_COPY|T_SOLID, color);
        }
      }

// UC_LEVEL_PGUPPGDOWN end
/*
      xx = (pr->xy2.x - pr->xy1.x + 3) / 4;
      yy = (pr->xy2.y - pr->xy1.y + 3) / 5;

      dot[1].x = (pr->xy2.x + pr->xy1.x) / 2;
      dot[0].x = dot[1].x - xx;
      dot[2].x = dot[1].x + xx;

      dot[1].y = ((pr->xy2.y + pr->xy1.y) / 2) - yy;
      dot[0].y =
      dot[2].y = dot[1].y + (yy * 2);

      if(dir == _DOWN)
      {
        dot[0].y = dot[1].y;
        dot[1].y = dot[2].y;
        dot[2].y = dot[0].y;
      }

      Polygon(3, dot, T_COPY|T_SOLID|T_FILL, color);
*/
    }
    else if(xx == 9)
    {
      xx = pr->xy1.x + 2;
      if(dir == _UP)
      {
        yy = pr->xy2.y - ((pr->xy2.y - pr->xy1.y) / 2);
        WritePixel(xx+2, yy-1, T_COPY|T_SOLID, color);
        Line(xx+1,   yy,   xx+3, yy,   T_COPY|T_SOLID, color);
        Line(xx, yy+1, xx+4, yy+1, T_COPY|T_SOLID, color);
      }
      else
      {
        yy = pr->xy1.y + ((pr->xy2.y - pr->xy1.y) / 2);
        WritePixel(xx+2, yy+1, T_COPY|T_SOLID, color);
        Line(xx+1,   yy,   xx+3, yy,   T_COPY|T_SOLID, color);
        Line(xx, yy-1, xx+4, yy-1, T_COPY|T_SOLID, color);
      }
    }
    else if(xx == 8)
    {
      xx = pr->xy1.x + 2;
      if(dir == _UP)
      {
        yy = pr->xy2.y - ((pr->xy2.y - pr->xy1.y) / 2);
        Line(xx,   yy,   xx+3, yy,   T_COPY|T_SOLID, color);
        Line(xx+1, yy-1, xx+2, yy-1, T_COPY|T_SOLID, color);
      }
      else
      {
        yy = pr->xy1.y + ((pr->xy2.y - pr->xy1.y) / 2);
        Line(xx,   yy,   xx+3, yy,   T_COPY|T_SOLID, color);
        Line(xx+1, yy+1, xx+2, yy+1, T_COPY|T_SOLID, color);
      }
    }
    else if(xx == 7)
    {
      xx = pr->xy1.x + 2;
      if(dir == _UP)
      {
        yy = pr->xy2.y - ((pr->xy2.y - pr->xy1.y) / 2);
        Line(xx,   yy,   xx+2, yy,   T_COPY|T_SOLID, color);
        WritePixel(xx+1, yy-1, T_COPY|T_SOLID, color);
      }
      else
      {
        yy = pr->xy1.y + ((pr->xy2.y - pr->xy1.y) / 2);
        Line(xx,   yy,   xx+2, yy,   T_COPY|T_SOLID, color);
        WritePixel(xx+1, yy+1, T_COPY|T_SOLID, color);
      }
    }
    else if(xx == 6)
    {
      xx = pr->xy1.x + 2;
      if(dir == _UP)
      {
        yy = pr->xy2.y - ((pr->xy2.y - pr->xy1.y) / 2);
        Line(xx,   yy,   xx+1, yy,   T_COPY|T_SOLID, color);
        Line(xx,   yy-1, xx+1, yy-1, T_COPY|T_SOLID, color);
      }
      else
      {
        yy = pr->xy1.y + ((pr->xy2.y - pr->xy1.y) / 2);
        Line(xx,   yy,   xx+1, yy,   T_COPY|T_SOLID, color);
        Line(xx,   yy+1, xx+1, yy+1, T_COPY|T_SOLID, color);
      }
    }
    else if(xx == 5)
    {
      xx = (pr->xy1.x + pr->xy2.x) / 2;
      Line(xx, pr->xy1.y+2, xx, pr->xy2.y-2, T_COPY|T_SOLID, color);
    }
  }
  else if((dir == _LEFT) || (dir == _RIGHT))
  {
    yy = pr->xy2.y - pr->xy1.y + 1;
    if(yy > 9)
    {
      xx = (pr->xy2.x - pr->xy1.x + 3) / 5;
      yy = (pr->xy2.y - pr->xy1.y + 3) / 4;

      dot[1].x = ((pr->xy2.x + pr->xy1.x) / 2) - xx;
      dot[0].x =
      dot[2].x = dot[1].x + (xx * 2);

      dot[1].y = (pr->xy2.y + pr->xy1.y) / 2;
      dot[0].y = dot[1].y - yy;
      dot[2].y = dot[1].y + yy;

      if(dir == _RIGHT)
      {
        dot[0].x = dot[1].x;
        dot[1].x = dot[2].x;
        dot[2].x = dot[0].x;
      }
      Polygon(3, dot, T_COPY|T_SOLID|T_FILL, color);
    }
    else if(yy == 9)
    {
      yy = pr->xy1.y + 2;
      if(dir == _LEFT)
      {
        xx = pr->xy2.x - ((pr->xy2.x - pr->xy1.x) / 2);
        WritePixel(xx-1, yy+2, T_COPY|T_SOLID, color);
        Line(xx,   yy+1, xx,   yy+3, T_COPY|T_SOLID, color);
        Line(xx+1, yy,   xx+1, yy+4, T_COPY|T_SOLID, color);
      }
      else
      {
        xx = pr->xy1.x + ((pr->xy2.x - pr->xy1.x) / 2);
        WritePixel(xx+1, yy+2, T_COPY|T_SOLID, color);
        Line(xx,   yy+1, xx,   yy+3, T_COPY|T_SOLID, color);
        Line(xx-1, yy,   xx-1, yy+4, T_COPY|T_SOLID, color);
      }
    }
    else if(yy == 8)
    {
      yy = pr->xy1.y + 2;
      if(dir == _LEFT)
      {
        xx = pr->xy2.x - ((pr->xy2.x - pr->xy1.x) / 2);
        Line(xx,   yy+1, xx,   yy+2, T_COPY|T_SOLID, color);
        Line(xx+1, yy,   xx+1, yy+3, T_COPY|T_SOLID, color);
      }
      else
      {
        xx = pr->xy1.x + ((pr->xy2.x - pr->xy1.x) / 2);
        Line(xx,   yy+1, xx,   yy+2, T_COPY|T_SOLID, color);
        Line(xx-1, yy,   xx-1, yy+3, T_COPY|T_SOLID, color);
      }
    }
    else if(yy == 7)
    {
      yy = pr->xy1.y + 2;
      if(dir == _LEFT)
      {
        xx = pr->xy2.x - ((pr->xy2.x - pr->xy1.x) / 2);
        WritePixel(xx,   yy+1, T_COPY|T_SOLID, color);
        Line(xx+1, yy,   xx+1, yy+2, T_COPY|T_SOLID, color);
      }
      else
      {
        xx = pr->xy1.x + ((pr->xy2.x - pr->xy1.x) / 2);
        WritePixel(xx,   yy+1, T_COPY|T_SOLID, color);
        Line(xx-1, yy,   xx-1, yy+2, T_COPY|T_SOLID, color);
      }
    }
    else if(yy == 6)
    {
      yy = pr->xy1.y + 2;
      if(dir == _LEFT)
      {
        xx = pr->xy2.x - ((pr->xy2.x - pr->xy1.x) / 2);
        Line(xx,   yy,   xx,   yy+1, T_COPY|T_SOLID, color);
        Line(xx-1, yy,   xx-1, yy+1, T_COPY|T_SOLID, color);
      }
      else
      {
        xx = pr->xy1.x + ((pr->xy2.x - pr->xy1.x) / 2);
        Line(xx  , yy,   xx  , yy+1, T_COPY|T_SOLID, color);
        Line(xx+1, yy,   xx+1, yy+1, T_COPY|T_SOLID, color);
      }

    }
    else if(yy == 5)
    {
      yy = (pr->xy1.y + pr->xy2.y) / 2;
      Line(pr->xy1.x+2, yy, pr->xy2.x-2, yy, T_COPY|T_SOLID, color);
    }
  }
 }
}

void ScrButton(_ROOM *proom, _BMP *pbmp, _ATTRIB att, _FRAMETYPE frame, _COLOR color, _COLOR frame_color, _UWORD dir)
{
  _ROOM tmp, room = *proom;
  _WORD h;

  if(pbmp == NULL)
  {
    if(frame < _THEMEFRAME)
    {
      DrawButton(&room, att, _3DFRAME, color, InvertColor_Makro(frame_color));
    }
    else
    {
      room.xy1.y -= 1;
      room.xy2.x += 1;
      DrawButton(&room, att, frame, color, color);
    }
  }
  else
  {
    room.xy1.x --;
    room.xy2.x ++;
    room.xy1.y --;
    out_zoom_BMP(&room, pbmp, T_SOLID);
  }

  if(dir == _PGUP)
  {
    tmp = room;
    h = ((tmp.xy2.y - tmp.xy1.y + 1)*3) / 4;
    tmp.xy2.y = tmp.xy1.y + h - 1;
    level_triangle(&tmp, _UP, GetBackColor_Makro(frame_color));
    tmp = room;
    tmp.xy1.y = tmp.xy2.y - h + 1;
    level_triangle(&tmp, _UP, GetBackColor_Makro(frame_color));
  }
  else if(dir == _PGDOWN)
  {
    tmp = room;
    h = ((tmp.xy2.y - tmp.xy1.y + 1)*3) / 4;
    tmp.xy1.y = tmp.xy2.y - h + 1;
    level_triangle(&tmp, _DOWN, GetBackColor_Makro(frame_color));
    tmp = room;
    tmp.xy2.y = tmp.xy1.y + h - 1;
    level_triangle(&tmp, _DOWN, GetBackColor_Makro(frame_color));
  }
  else
  {
    level_triangle(&room, dir, GetBackColor_Makro(frame_color));
  }
}

void level_draw(_LEVEL *p, _BOOL horizontal, _BOOL firsttime, _BMP *pbmp, _FRAMETYPE frame)
{
  _ATTRIB att = T_SOLID|T_COPY|T_FILL;
  _ROOM   room;
  _COLOR  tmp, color = InvertColor_Makro(p->color);

  if(p->active == _TRUE)
  {
   #ifdef UC_MOUSE
    _UWORD hide = IfNecHideMouseCursor(&p->room);
   #endif

    if(frame < _THEMEFRAME)
    {
      DrawButton(&p->room, att, _3DFRAME, p->color, p->frame_color);
    }
    else
    {
      DrawButton(&p->room, att|T_INVERTTHEME, frame, p->color, p->frame_color);
//      DrawButton(&p->room, att^T_INVRS, frame, p->color, p->frame_color);

      tmp = GetPenColor_Makro(p->frame_color);
      if(tmp != INVISIBLE)
        color = MakeColor_Makro(tmp, tmp);
    }

    if(horizontal == _FALSE)
    {
//      WritePixel(p->room.xy1.x, p->room.xy2.y, att, GetPenColor_Makro(p->frame_color));

      room.xy1.x = p->room.xy1.x + 1;
      room.xy2.x = p->room.xy2.x - 1;
      room.xy1.y = p->room.xy1.y + 1;
      room.xy2.y = room.xy1.y + LEVELBUTTON_HEIGHT;

      if(p->pguppgdown == _TRUE)
      {
        ScrButton(&room, pbmp, att, frame, color, p->frame_color, LEVELBUTTON_TOP1);
        room.xy1.y = room.xy2.y + 1;
        room.xy2.y = room.xy1.y + LEVELBUTTON_HEIGHT;
        ScrButton(&room, pbmp, att, frame, color, p->frame_color, LEVELBUTTON_TOP2);
      }
      else
      {
        ScrButton(&room, pbmp, att, frame, color, p->frame_color, _UP);
      }

      room.xy2.y = p->room.xy2.y; // - 1;
      if(frame < _THEMEFRAME)
        room.xy2.y -= 1;
      room.xy1.y = room.xy2.y - LEVELBUTTON_HEIGHT;

      if(p->pguppgdown == _TRUE)
      {
        ScrButton(&room, pbmp, att, frame, color, p->frame_color, LEVELBUTTON_BOTTOM1);
        room.xy2.y = room.xy1.y - 1;
        room.xy1.y = room.xy1.y - LEVELBUTTON_HEIGHT;
        ScrButton(&room, pbmp, att, frame, color, p->frame_color, LEVELBUTTON_BOTTOM2);
      }
      else
      {
        ScrButton(&room, pbmp, att, frame, color, p->frame_color, _DOWN);
      }

/*
      if(pbmp == NULL)
      {
        if(frame < _THEMEFRAME)
        {
          DrawButton(&room, att, _3DFRAME, color, InvertColor_Makro(p->frame_color));
        }
        else
        {
          room.xy2.y += 1;
          DrawButton(&room, att, frame, color, color);
        }
      }
      else
      {
        room.xy2.y ++;
        out_zoom_BMP(& room, pbmp, T_SOLID);
      }

      level_triangle(&room, _DOWN, GetBackColor_Makro(p->frame_color));
*/
    }
    else
    {
//      WritePixel(p->room.xy1.x, p->room.xy1.y, att, GetPenColor_Makro(p->frame_color));

      room.xy1.x = p->room.xy1.x + 1;
      room.xy2.x = room.xy1.x + LEVELBUTTON_HEIGHT;
      room.xy1.y = p->room.xy1.y + 1;
      room.xy2.y = p->room.xy2.y - 1;
      if(pbmp == NULL)
      {
        if(frame < _THEMEFRAME)
        {
          DrawButton(&room, att, _3DFRAME, color, InvertColor_Makro(p->frame_color));
        }
        else
        {
          room.xy1.x -= 1;
          room.xy2.y += 1;
          DrawButton(&room, att, frame, color, color);
        }
      }
      else
      {
        room.xy1.x --;
        room.xy2.y ++;
        room.xy1.y --;
        out_zoom_BMP(& room, pbmp, T_SOLID);
      }

      level_triangle(&room, _LEFT, GetBackColor_Makro(p->frame_color));

      room.xy2.x = p->room.xy2.x - 1;
      room.xy1.x = room.xy2.x - LEVELBUTTON_HEIGHT;
      if(pbmp == NULL)
      {
        if(frame < _THEMEFRAME)
        {
          DrawButton(&room, att, _3DFRAME, color, InvertColor_Makro(p->frame_color));
        }
        else
        {
          room.xy2.x += 1;
          DrawButton(&room, att, frame, color, color);
        }
      }
      else
      {
        room.xy2.x ++;
        out_zoom_BMP(& room, pbmp, T_SOLID);
      }

      level_triangle(&room, _RIGHT, GetBackColor_Makro(p->frame_color));
    }

   #ifdef UC_MOUSE
    IfNecShowMouseCursor(hide);
   #endif

    if(firsttime == _TRUE)
      p->old_pos = -1;
    else
      p->old_pos = 0;

  }
}

void level_run(_LEVEL *p, _DWORD no, _DWORD pos, _BOOL horizontal, _BMP *pbmp, _FRAMETYPE frame)
{
  _KOORD  x, x1, x2, w;
  _KOORD  y, y1, y2, h;
  _ROOM   room;
  _ATTRIB att = T_COPY|T_SOLID|T_FILL;
  _COLOR  color;
 #ifdef UC_MOUSE
  _UWORD hide;
 #endif

  if(p->active == _TRUE)
  {
    if(horizontal == _FALSE)
    {
//      y1 = p->room.xy1.y + LEVELBUTTON_HEIGHT + 3;
//      y2 = p->room.xy2.y - LEVELBUTTON_HEIGHT - 3;
      y1 = p->room.xy1.y + LEVELBUTTON_HEIGHT + 2;
      y2 = p->room.xy2.y - LEVELBUTTON_HEIGHT - 2;
      if(p->pguppgdown == _TRUE)
      {
        y1 += LEVELBUTTON_HEIGHT + 1;
        y2 -= LEVELBUTTON_HEIGHT - 1;
        h  = y2 - y1 - LEVELBUTTON_HEIGHT - 1;
      }
      else
      {
        h = y2 - y1 - LEVELBUTTON_HEIGHT;
      }

      if(h > 0)
      {
        if((pos == 0)||(no < 2))
        {
          y = 0;
        }
        else if(pos >= (no-1))
        {
          y = h;
        }
        else
        {
          y = (h * pos)/(no-1);
        }

        if((y != p->old_pos)||(p->old_pos == -1))
        {
          room.xy1.x = p->room.xy1.x + 1;
          room.xy2.x = p->room.xy2.x - 1;

          if(p->old_pos >= 0)
          {
            if(is_invisible(p->color, att) == _FALSE)
            {
              room.xy1.y = y1 + p->old_pos;
//              room.xy2.y = room.xy1.y + LEVELBUTTON_HEIGHT+1;
              room.xy2.y = room.xy1.y + LEVELBUTTON_HEIGHT;

             #ifdef UC_MOUSE
              hide = IfNecHideMouseCursor(&room);
             #endif
             #ifdef UC_THEME
              if(frame < _THEMEFRAME)
             #endif
              {
                Bar(room.xy1.x, room.xy1.y, room.xy2.x, room.xy2.y, att, p->color); //p->color);
              }
             #ifdef UC_THEME
              else
              {
                room.xy1.x -= 1;
                room.xy2.x += 1;
                draw_THEME_part(&room, frame, T_COPY|T_SOLID, p->color, _TRUE, horizontal);
              }
             #endif
             #ifdef UC_ROTATE
              RefreshRectangle(&room);
             #endif
             #ifdef UC_MOUSE
              IfNecShowMouseCursor(hide);
             #endif
            }
          }
          p->old_pos = y;
          room.xy1.y = y1 + y;
          room.xy2.y = room.xy1.y + LEVELBUTTON_HEIGHT;
         #ifdef UC_MOUSE
          hide = IfNecHideMouseCursor(&room);
         #endif
          if(pbmp == NULL)
          {
            if(frame < _THEMEFRAME)
            {
              DrawButton(&room, att, _3DFRAME, InvertColor_Makro(p->color), InvertColor_Makro(p->frame_color));
            }
            else
            {
              color = GetPenColor_Makro(p->frame_color);
              if(color != INVISIBLE)
                color = MakeColor_Makro(color, color);
              else
                color = GetBackColor_Makro(p->color);
              room.xy1.x = p->room.xy1.x + 1;
              room.xy2.x = p->room.xy2.x;
              DrawButton(&room, att, frame, color, color);
            }
          }
          else
          {
            out_zoom_BMP(&room, pbmp, T_SOLID);
          }

         #ifdef UC_ROTATE
          RefreshRectangle(&room);
         #endif
         #ifdef UC_MOUSE
          IfNecShowMouseCursor(hide);
         #endif
        }
      }
    }
    else
    {
//      x1 = p->room.xy1.x + LEVELBUTTON_HEIGHT + 3;
//      x2 = p->room.xy2.x - LEVELBUTTON_HEIGHT - 3;
      x1 = p->room.xy1.x + LEVELBUTTON_HEIGHT + 2;
      x2 = p->room.xy2.x - LEVELBUTTON_HEIGHT - 2;

      w  = x2 - x1 - LEVELBUTTON_HEIGHT;

      if(w > 0)
      {
        if(pos == 0)
        {
          x = 0;
        }
        else if(pos >= (no-1))
        {
          x = w;
        }
        else
        {
          x = (w * pos)/(no-1);
        }

        if((x != p->old_pos)||(p->old_pos == -1))
        {
          room.xy1.y = p->room.xy1.y + 1;
          room.xy2.y = p->room.xy2.y - 1;

          if(p->old_pos >= 0)
          {
            if(is_invisible(p->color, att) == _FALSE)
            {
              room.xy1.x = x1 + p->old_pos;
//              room.xy2.x = room.xy1.x + LEVELBUTTON_HEIGHT+1;
              room.xy2.x = room.xy1.x + LEVELBUTTON_HEIGHT;

             #ifdef UC_MOUSE
              hide = IfNecHideMouseCursor(&room);
             #endif
             #ifdef UC_THEME
              if(frame < _THEMEFRAME)
             #endif
              {
                Bar(room.xy1.x, room.xy1.y, room.xy2.x, room.xy2.y, att, p->color);
              }
             #ifdef UC_THEME
              else
              {
                room.xy1.y -= 1;
                room.xy2.y += 1;
                draw_THEME_part(&room, frame, T_SOLID|T_COPY, p->color, _TRUE, horizontal);
              }
             #endif
             #ifdef UC_ROTATE
              RefreshRectangle(&room);
             #endif
             #ifdef UC_MOUSE
              IfNecShowMouseCursor(hide);
             #endif
            }
          }

          p->old_pos = x;
          room.xy1.x = x1 + x;
          room.xy2.x = room.xy1.x + LEVELBUTTON_HEIGHT;
         #ifdef UC_MOUSE
          hide = IfNecHideMouseCursor(&room);
         #endif
          if(pbmp == NULL)
          {
            if(frame < _THEMEFRAME)
            {
              DrawButton(&room, att, _3DFRAME, InvertColor_Makro(p->color), InvertColor_Makro(p->frame_color));
            }
            else
            {
              color = GetPenColor_Makro(p->frame_color);
              if(color != INVISIBLE)
                color = MakeColor_Makro(color, color);
              else
                color = GetBackColor_Makro(p->color);
              room.xy1.y = p->room.xy1.y + 1;
              room.xy2.y = p->room.xy2.y;
              DrawButton(&room, att, frame, color, color);
            }
          }
          else
          {
            out_zoom_BMP(&room, pbmp, T_SOLID);
          }
         #ifdef UC_ROTATE
          RefreshRectangle(&room);
         #endif
         #ifdef UC_MOUSE
          IfNecShowMouseCursor(hide);
         #endif
        }
      }
    }
  }
}

void level_out(_LEVEL *p, _UDWORD no, _DWORD pos, _BOOL horizontal, _BMP *pbmp, _FRAMETYPE frame)
{
  level_draw(p, horizontal, _TRUE, pbmp, frame);
  level_run(p, no, pos, horizontal, pbmp, frame);
}

void chk_position_SCROLL(_SCROLL *p)
{
  _ROOM  room;
  _KOORD xcorr = 0, ycorr = 0;

  MyGetScreenSize(&room);
  room.xy2.y -= (SetUp.GetSoftkeyHeight() + POPUP_SHADOW);
  room.xy2.x -= POPUP_SHADOW;

  if(p->out_room.xy2.x > room.xy2.x)
	 xcorr = p->out_room.xy2.x - room.xy2.x;

  if(p->out_room.xy1.x < room.xy1.x)
	 xcorr = p->out_room.xy1.x - room.xy1.x;

  if(p->out_room.xy2.y > room.xy2.y)
	 ycorr = p->out_room.xy2.y - room.xy2.y;

  if(p->out_room.xy1.y < room.xy1.y)
	 ycorr = p->out_room.xy1.y - room.xy1.y;

  p->out_room.xy1.x    -= xcorr;
  p->out_room.xy2.x    -= xcorr;
  p->scroll_room.xy1.x -= xcorr;
  p->scroll_room.xy2.x -= xcorr;
  p->level.room.xy1.x  -= xcorr;
  p->level.room.xy2.x  -= xcorr;

  p->out_room.xy1.y    -= ycorr;
  p->out_room.xy2.y    -= ycorr;
  p->scroll_room.xy1.y -= ycorr;
  p->scroll_room.xy2.y -= ycorr;
  p->level.room.xy1.y  -= ycorr;
  p->level.room.xy2.y  -= ycorr;
}


#ifdef HID
_UDWORD avoid_jiggle;
_UWORD find_HID_SCROLL(_EVENT *pe, _BOOL edge, _LEVEL *pl, _POSITION *pp, _LEVEL *phl, _POSITION *php, _ROOM *scroll_room, _UWORD line_height, _UWORD column_width)
{
  _UWORD  retcode = _NOKEY;
  _UDWORD pos, h, y;
  _DOT    *pd = &pe->dot;


  if(edge == _TRUE)
  {
    if(pl != NULL)
      pl->drag = _FALSE;
    if(phl != NULL)
      phl->drag = _FALSE;
  }

  // hid in level - vertical
  if((pl != NULL) && (pp != NULL) &&
     (pl->active == _TRUE) &&
     (pd->x >= pl->room.xy1.x) && (pd->x <= pl->room.xy2.x) &&
     (pd->y >= pl->room.xy1.y) && (pd->y <= pl->room.xy2.y))
  {
    if(pp->no > 0)
    {
      if(edge == _TRUE)
      {
        if(pl->pguppgdown == _TRUE)
        {
          if(pd->y <= (pl->room.xy1.y+LEVELBUTTON_HEIGHT))
          {
            retcode = LEVELBUTTON_TOP1;
          }
          else if(pd->y <= (pl->room.xy1.y+LEVELBUTTON_HEIGHT*2))
          {
            retcode = LEVELBUTTON_TOP2;
          }
          else if(pd->y >= (pl->room.xy2.y-LEVELBUTTON_HEIGHT))
          {
            retcode = LEVELBUTTON_BOTTOM1;
          }
          else if(pd->y >= (pl->room.xy2.y-LEVELBUTTON_HEIGHT*2))
          {
            retcode = LEVELBUTTON_BOTTOM2;
          }
//        else if(pd->y <= (pl->room.xy1.y + LEVELBUTTON_HEIGHT*2 + pl->old_pos))
//        {
//        if(avoid_jiggle != _PGDOWN)
//            retcode = _PGUP;
//        }
//        else if(pd->y >= (pl->room.xy1.y + (LEVELBUTTON_HEIGHT*3) + pl->old_pos))
//        {
//          if(avoid_jiggle != _PGUP)
//            retcode = _PGDOWN;
//        }
          else  // hid on level
          {
            pl->drag = _TRUE;
          }
        }
        else
        {
          if(pd->y <= (pl->room.xy1.y+LEVELBUTTON_HEIGHT))
          {
            retcode = _UP;
          }
          else if(pd->y >= (pl->room.xy2.y-LEVELBUTTON_HEIGHT))
          {
            retcode = _DOWN;
          }
          else if(pd->y <= (pl->room.xy1.y + LEVELBUTTON_HEIGHT + pl->old_pos))
          {
           #ifdef USER_BILLION
            if(pp->no > pp->height)
           #endif
            if(avoid_jiggle != _PGDOWN)
              retcode = _PGUP;
          }
          else if(pd->y >= (pl->room.xy1.y + (LEVELBUTTON_HEIGHT*2) + pl->old_pos))
          {
           #ifdef USER_BILLION
            if(pp->no > pp->height)
           #endif
            if(avoid_jiggle != _PGUP)
              retcode = _PGDOWN;
          }
          else  // hid on level
          {
            pl->drag = _TRUE;
          }
        }

        if(retcode != _NOKEY)
        {
          pl->drag = _FALSE;
          if(pl->trigger_state == _FALSE)
          {
            pl->trigger_state = Keyboard.TriggerEventStart(pe, _TIPCOMBI);
            avoid_jiggle = retcode;
          }
        }
      }

      if(pl->drag == _TRUE)  // level drag and drop
      {
        if(pl->pguppgdown == _TRUE)
        {
          if(pd->y < (pl->room.xy1.y + (LEVELBUTTON_HEIGHT*2 + LEVELBUTTON_HEIGHT/2)))
          {
            pp->pos = 0;
          }
          else if(pd->y > (pl->room.xy2.y - (LEVELBUTTON_HEIGHT*2 + LEVELBUTTON_HEIGHT/2)))
          {
            pp->pos = pp->no - 1;
          }
          else
          {
            h = (pl->room.xy2.y - pl->room.xy1.y + 1) - (LEVELBUTTON_HEIGHT * 5);
            y = pd->y - (pl->room.xy1.y + LEVELBUTTON_HEIGHT*2 + LEVELBUTTON_HEIGHT/2);

            if(pp->lineheight == NULL)
            {
              y = AMBDC(y, pp->no, h);
              if(y < pp->no)
                pp->pos = y;
            }
            else
            {
              y = AMBDC(y, pp->totalheight, h);
              y = get_line_no(pp, y);
              if(y < pp->no)
                pp->pos = y;
            }
          }
        }
        else
        {
          if(pd->y < (pl->room.xy1.y + (LEVELBUTTON_HEIGHT + LEVELBUTTON_HEIGHT/2)))
          {
            pp->pos = 0;
          }
          else if(pd->y > (pl->room.xy2.y - (LEVELBUTTON_HEIGHT + LEVELBUTTON_HEIGHT/2)))
          {
            pp->pos = pp->no - 1;
          }
          else
          {
            h = (pl->room.xy2.y - pl->room.xy1.y + 1) - (LEVELBUTTON_HEIGHT * 3);
            y = pd->y - (pl->room.xy1.y + LEVELBUTTON_HEIGHT + LEVELBUTTON_HEIGHT/2);

            if(pp->lineheight == NULL)
            {
              y = AMBDC(y, pp->no, h);
              if(y < pp->no)
                pp->pos = y;
            }
            else
            {
              y = AMBDC(y, pp->totalheight, h);
              y = get_line_no(pp, y);
              if(y < pp->no)
                pp->pos = y;
            }
          }
        }
      }
    }
  }

  // hid in level - horizontal
  else if((phl != NULL) && (php != NULL) &&
     (phl->active == _TRUE) &&
     (pd->x >= phl->room.xy1.x) && (pd->x <= phl->room.xy2.x) &&
     (pd->y >= phl->room.xy1.y) && (pd->y <= phl->room.xy2.y))
  {
    if(php->no > 0)
    {
      if(edge == _TRUE)
      {
        if(pd->x <= (phl->room.xy1.x+LEVELBUTTON_WIDTH))
        {
          retcode = _LEFT;
        }
        else if(pd->x >= (phl->room.xy2.x-LEVELBUTTON_WIDTH))
        {
          retcode = _RIGHT;
        }
        else if(pd->x <= (phl->room.xy1.x + LEVELBUTTON_WIDTH + phl->old_pos))
        {
          if(avoid_jiggle != _PGRIGHT)
            retcode = _PGLEFT;
        }
        else if(pd->x >= (phl->room.xy1.x + (LEVELBUTTON_WIDTH*2) + phl->old_pos))
        {
          if(avoid_jiggle != _PGLEFT)
            retcode = _PGRIGHT;
        }
        else  // hid on level
        {
          phl->drag = _TRUE;
        }

        if(retcode != _NOKEY)
        {
          phl->drag = _FALSE;
          if(phl->trigger_state == _FALSE)
          {
            phl->trigger_state = Keyboard.TriggerEventStart(pe, _TIPCOMBI);
            avoid_jiggle = retcode;
          }
        }
      }

      if(phl->drag == _TRUE)  // level drag and drop
      {
        if(pd->x < (phl->room.xy1.x + (LEVELBUTTON_WIDTH + LEVELBUTTON_WIDTH/2)))
        {
          php->pos = 0;
        }
        else if(pd->x > (phl->room.xy2.x - (LEVELBUTTON_WIDTH + LEVELBUTTON_WIDTH/2)))
        {
          php->pos = php->no - 1;
        }
        else
        {
          h = (phl->room.xy2.x - phl->room.xy1.x + 1) - (LEVELBUTTON_WIDTH * 3);
          y = pd->x - (phl->room.xy1.x + LEVELBUTTON_WIDTH + LEVELBUTTON_WIDTH/2);
          y = AMBDC(y, php->no, h);
          if(y < php->no)
            php->pos = y;
        }

      }

    }

  }

  // hid in scrollarea
  else if((pd->x >= scroll_room->xy1.x) && (pd->x <= scroll_room->xy2.x) &&
          (pd->y >= scroll_room->xy1.y) && (pd->y <= scroll_room->xy2.y))
  {
    // vertical
    if(pp != NULL)
    {
      pos = pp->begin + (pd->y - scroll_room->xy1.y) / line_height;
     #ifdef ENTER_ON_NEGEDGE
      if(edge == _TRUE)
      {
        if(pos != pp->pos)
          pp->pos = pos;
      }
      else
      {
        if(pos == pp->pos)
          retcode = _ENTER;
      }
     #else
      if(edge == _TRUE)
      {
        if(pos != pp->pos)
        {
          pp->pos = pos;
          if(SetUp.GetDoubleClickOption() == _TRUE)
		  {
            retcode = _ENTER;
            Beep(BEEP_SCROLLCONFIRM);
          }
		  else
          {
            Beep(BEEP_SCROLLSELECT);
          }
        }
        else if(pos == pp->pos)
        {
          retcode = _ENTER;
          Beep(BEEP_SCROLLCONFIRM);
        }
      }
     #endif
    }
    // horizontal
    if(php != NULL)
    {
      pos = php->begin + (pd->x - scroll_room->xy1.x) / column_width;  // /1 wird später geändert
     #ifdef ENTER_ON_NEGEDGE
      if(edge == _TRUE)
      {
        if(pos != php->pos)
          php->pos = pos;
      }
      else
      {
        if(pos == php->pos)
          retcode = _ENTER;
      }
     #else
      if(edge == _TRUE)
      {
        if(pos != php->pos)
          php->pos = pos;
        else if(pos == php->pos)
          retcode = _ENTER;
      }
     #endif
    }

  }
/*
  else if((pd->x < pm->out_room.xy1.x) || (pd->x > pm->out_room.xy2.x) ||
          (pd->y < pm->out_room.xy1.y) || (pd->y > pm->out_room.xy2.y))
  {
    // hid out of popup
    if(edge == _TRUE)
      retcode = _ESC;
  }
*/
  return(retcode);
}

// Old interface
_BOOL track_HID_SCROLL(_EVENT *pe, _LEVEL *pl, _POSITION *pp, _ROOM *scroll_room, _UWORD lineheight)
{

  return(do_HID_SCROLL(pe, pl, pp, NULL, NULL, scroll_room, lineheight, 1));
}

_BOOL do_HID_SCROLL(_EVENT *pe, _LEVEL *pl, _POSITION *pp, _LEVEL *phl, _POSITION *php, _ROOM *scroll_room, _UWORD lineheight, _UWORD columnwidth)
{
  _BOOL  retcode  = _FALSE;
  _UWORD scancode = _NOKEY;

  if((pe->ftype == _EVENT_HIDPRESS)&&(pe->button == _HID_LEFT))
  {
    avoid_jiggle = _NOKEY;
    scancode = find_HID_SCROLL(pe, _TRUE, pl, pp, phl, php, scroll_room, lineheight, columnwidth);
    if((scancode != _NOKEY) && (scancode != _ENTER))
      Beep(BEEP_LEVEL);
  }
  else if((pe->ftype == _EVENT_HIDRELEASE)&&(pe->button == _HID_LEFT))
  {
    avoid_jiggle = _NOKEY;
   #ifdef ENTER_ON_NEGEDGE
    scancode = find_HID_SCROLL(pe, _FALSE, pl, pp, phl, php, scroll_room, lineheight, columnwidth);
   #endif
    if(pl != NULL)
    {
      pl->trigger_state = _FALSE;
      pl->drag      = _FALSE;
    }
    if(phl != NULL)
    {
      phl->trigger_state = _FALSE;
      phl->drag      = _FALSE;
    }
  }
  else if((pe->ftype == _EVENT_KEYRELEASE)||(pe->ftype == _EVENT_KEYPRESS))
  {
    avoid_jiggle = _NOKEY;
    if(pl != NULL)
      pl->trigger_state = _FALSE;
    if(phl != NULL)
      phl->trigger_state = _FALSE;
  }
  else if(pe->ftype == _EVENT_TRIGGER)
  {
    scancode = find_HID_SCROLL(pe, _TRUE, pl, pp, phl, php, scroll_room, lineheight, columnwidth);
  }
  else if(pe->ftype == _EVENT_HIDMOVE) // just for level drag and drop
  {
    scancode = find_HID_SCROLL(pe, _FALSE, pl, pp, phl, php, scroll_room, lineheight, columnwidth);
  }

  if(scancode != _NOKEY)
  {
    pe->ftype    = _EVENT_KEYPRESS;
    pe->scancode = scancode;
    retcode      = _TRUE;
  }

  return(retcode);
}

_BOOL is_HID_SCROLL(_EVENT *pe, _SCROLL *p)
{
  _BOOL retcode = _FALSE;
  _ROOM room;

  if(pe->ftype == _EVENT_HIDPRESS)
  {
    room = p->scroll_room;

    if((pe->dot.x >= room.xy1.x)&&(pe->dot.y >= room.xy1.y)&&
       (pe->dot.x <= room.xy2.x)&&(pe->dot.y <= room.xy2.y))
    {
      retcode = _TRUE;
    }
    else if(p->level.active == _TRUE)
    {
      room = p->level.room;
      if((pe->dot.x >= room.xy1.x)&&(pe->dot.y >= room.xy1.y)&&
         (pe->dot.x <= room.xy2.x)&&(pe->dot.y <= room.xy2.y))
      {
        retcode = _TRUE;
      }
    }
  }

  return(retcode);
}

#endif

void OutDraw_SCROLL(_SCROLL *p)
{
  OutDraw_SCROLL_sub(p, _TRUE);
}

void OutLine_SCROLL(_SCROLL *p, _UDWORD y, _UDWORD no, _BOOL st, _BOOL redraw_background)
{
  OutLine_SCROLL_sub(p, y, no, st, redraw_background, _TRUE);
}

void Beam_SCROLL(_SCROLL *p, _UDWORD y, _UDWORD no, _BOOL st)
{
  Beam_SCROLL_sub(p, y, no, st, _TRUE);
}

