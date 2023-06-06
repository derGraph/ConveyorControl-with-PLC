#include "T_IPC.H"
#include "T_NUC.H"

#include "COMINTFC.H"

//#define MENUE_CURSOR_ALT

void  draw_window(_MENU*, _CHAR*, _BOOL);
void  calculate_window(_MENUCALCUL*, _MENUINFO*, _POSITION*, _MENUPOINTER*);

_BOOL _Window::CallInputIsSavedOnSign(_VARLABEL *value, _BOOL lrm)
{
  _BOOL       retcode = _FALSE;
  _RESULT     result;
  _VARIABLE   variable;
  _MY_PICTURE *pmp;

  if(Sign == _TRUE)
  {
    if(P_Picture != NULL)
    {
      if(P_Picture->IsEditorOpen() == _TRUE)
      {
        init_RESULT_Makro(&result);
        init_VARIABLE_Makro(&variable);
        set_lrm(&result, lrm);
        if(VarList.GetSystemData(&result, &variable, value, _TRUE, _TRUE) == _TRUE)
        {
          pmp = P_Picture->GetMyPicture();
          input_is_saved(&pmp->Editor.input, &result);
          retcode = _TRUE;
        }
        free_VARIABLE(&variable);
//        free_RESULT(&result);
      }
    }
  }
  else if(P_Background != NULL)
  {
    P_Background->CallInputIsSavedOnSign(value, lrm);
  }

  return(retcode);
}

#ifdef PATRICK
_BOOL _Window::CheckForClose(void)
{
  if(P_Picture != NULL)
    return(P_Picture->CheckForClose());

  if(P_Background != NULL)
    return(P_Background->CheckForClose());

  return(_FALSE);
}
#endif

void popup_mae_run(_Window *Pw, _PopUp *Pp, _EVENT *pe)
{
  _MENU       *pm;
  _LINEINFO   *pli;
  _VARLABEL   *pv;
  _STACK_LINE sl;
  _BOOL       state, doret, saval;

 #ifdef PATRICK
  pv = Pp->GetInput();
  if(chk_VARLABEL(pv) == _TRUE)
  {
    if(Pw->CheckForClose() == _TRUE) // überprüfen ob eingabeberechtigung noch besteht, ansonsten menue schliessen
    {
      init_STACK_LINE_Makro(&sl);
      sl.cmd = CMD_RETURN_TO_SIGN;
      sl.op1.no = 1;
      sl.op1.info[0].state = CONST_VAL;
      sl.op1.info[0].value = _ESC;
      Pw->AddLine(&sl, _FALSE);                                      // exit
      free_STACK_LINE(&sl);
    }
  }
 #endif

  if(pe->ftype == _EVENT_KEYPRESS)
  {
    if((pe->scancode == _ENTER)||(pe->scancode == _RIGHT))
    {
      pm  = Pp->GetMenu();
      pli = MenuList.Get_LINEINFO(pm->pointer.Ptr_LSEMENU, pm->position.pos);

      if(pli != NULL)
      {
        if(state_LINEINFO(pli) == STATE_ACTIVE)
        {
          if(pe->scancode == _RIGHT)
          {
            if(lookup_LSEFUNCT(&pli->gfunct.pos_fl, CMD_NEWPOPUP) == _TRUE)
            {
              Pw->Add_LSEFUNCT(&pli->gfunct.pos_fl, pe->lrm);
            }
          }
          else if(pe->scancode == _ENTER)
          {
            // standard funktionalität ausführen
            saval = _TRUE; // save editor
            doret = _TRUE; // direction on enter

            if(InterBoxList.Chk_LSEFUNCT(&pli->gfunct.pos_fl) == _TRUE)
            {
              // user hat eigene funktion definiert
              saval = lookup_LSEFUNCT(&pli->gfunct.pos_fl, CMD_SAVEEDITOR);
              doret = lookup_LSEFUNCT(&pli->gfunct.pos_fl, CMD_RETURN);
              Pw->Add_LSEFUNCT(&pli->gfunct.pos_fl, pe->lrm);    // andere funktionalität in queue
            }

            state = _FALSE;
            if(saval == _TRUE)
            {
              pv = Pp->GetInput();
              if(chk_VARLABEL(pv) == _TRUE)
              {
                
                _DOIT doit = _IDLE;
                if(Pp->GetP_MyIo() != NULL)
                {
                  _RESULT   m_result;
                  _VARIABLE m_var;
                  if(VarList.GetSystemData(&m_result, &m_var, &pli->value, _TRUE, _TRUE) == _TRUE)
                  {
                    doit = CallMethod_MyIoSetValue(&m_result, pv, Pp->GetP_MyIo());
                  }
                }
                
                if(doit == _IDLE)
                {
                  init_STACK_LINE_Makro(&sl);
                  sl.cmd = CMD_SET;
                  sl.op1 = *pv;
                  sl.op2 = pli->value;
                  state = do_CMD_SET(&sl, pe->lrm);   // save
                  if(state == _TRUE)
                    doit = _IDIDIT;
                  free_STACK_LINE(&sl);
                }
                
                if(doit == _IDIDIT)
                  Pw->CallInputIsSavedOnSign(&pli->value, pe->lrm); // call interface input is saved
              }
            }

            if(doret == _TRUE)
            {
              init_STACK_LINE_Makro(&sl);
              sl.cmd = CMD_RETURN_TO_SIGN;
              sl.op1.no = 1;
              sl.op1.info[0].state = CONST_VAL;
              sl.op1.info[0].value = (state == _TRUE)? _ENTER : _ESC;   // call direction on enter
              // sl.op2 = pli->value;
              Pw->AddLine(&sl, pe->lrm);                                      // exit
              free_STACK_LINE(&sl);
            }
          }
        }
      }
    }
    else if(pe->scancode == _LEFT)
    {
      pe->scancode = _ESC;
    }
  }
}

void popup_mae_line(_Window *Pw, _PopUp *Pp, _UDWORD no, _ROOM *r, _COLOR col, _BOOL background)
{
  _ROOM   room;
  _CHAR   *txt;
  _MENU   *pm;
  _COLOR  c;
  _UDWORD stscheme_result;

  room = *r;
  room.xy1.x += 2;

  pm = Pp->GetMenu();

  if(pm->info.frametype >= _THEMEFRAME)
    room.xy1.x += 4;

  if(background == _TRUE)
  {
    if(pm->info.frametype < _THEMEFRAME)
    {
      Bar(r->xy1.x, r->xy1.y, r->xy2.x, r->xy2.y, T_COPY|T_SOLID, InvertColor_Makro(col));
    }
    else
    {
      c = GetBackColor_Makro(col);
      c = MakeColor_Makro(c, c);
      DrawButton(&pm->calcul.out_room, pm->info.attrib, pm->info.frametype, c, c); // T_COPY|T_SOLID
    }
  }

  txt = MenuList.GetLineText(&stscheme_result, pm->pointer.Ptr_LSEMENU, no);
  if(txt != NULL)
  {
    _KOORD x, y;
    _ATTRIB att = pm->info.attrib;
    //_ATTRIB att = T_COPY | T_SOLID | T_PROP | T_CENTERBOUND | T_DOWNBOUND; // test
    switch(att & T_HORIZBOUND)
    {
      case T_CENTERBOUND:
        x = (room.xy1.x + room.xy2.x) / 2;
        break;
      case T_RIGHTBOUND:
        x = room.xy2.x;
        break;
      default:
        x = room.xy1.x;
        break;
    }
    
    switch(att & T_VERTBOUND)
    {
      case T_MIDBOUND:
        y = (room.xy1.y + room.xy2.y) / 2;
        break;
      case T_DOWNBOUND:
        y = room.xy2.y;
        break;
      default:
        y = room.xy1.y;
        break;
    }
        
    if(stscheme_result == STATE_INACTIVE)    
        col = pm->info.inactive_text_color;
        
    col = GetPenColor_Makro(col);
    if(col != INVISIBLE)
      OutMultiTextIconXY(x, y, txt, att, MakeColor_Makro(INVISIBLE, col), sizeof(_CHAR), pm->info.font);
  }

 #ifdef UC_ROTATE
  RefreshRectangle((background == _TRUE)? r:&room);
 #endif
  
}

void _PopUp::Free(void)
{
  Cursor.Free();
  free_REGION(&Region);
  free_MENU(&Menu);
  free_VARLABEL(&Input);
  Init();
}

void _PopUp::Init(void)
{
  P_Window = NULL;
  Cursor.Init();
  init_REGION(&Region);
  init_MENU(&Menu);
  init_VARLABEL_Makro(&Input);
  init_VARLABEL_Makro(&ImOverloaded);
  pUser = NULL;
  P_MyIo = NULL;
}

void _PopUp::Calculate(void)
{
  calculate_window(&Menu.calcul, &Menu.info, &Menu.position, &Menu.pointer);
}

void _PopUp::GetLinePosition(_UWORD y, _ROOM *pr)
{
  *pr        = Menu.calcul.scroll_room;
  pr->xy1.y += y * Menu.info.line_height;
  pr->xy2.y  = pr->xy1.y + Menu.info.line_height - 1;
}

void _PopUp::Beam(_UWORD y, _UWORD no, _BOOL st, _BOOL do_refresh)
{
  _COLOR col, cb, cf;

  if(st == _TRUE)
  {
   #ifdef MENUE_CURSOR_ALT
    col = Menu.info.bar_color;
   #else
    cb  = SetUp.GetEditColorBack(_EDITACTIVE, GetBackColor_Makro(Menu.info.text_color));
    cf  = SetUp.GetEditColorTxt(_EDITACTIVE, GetPenColor_Makro(Menu.info.text_color));
    col = MakeColor_Makro(cb, cf);
   #endif
  }
  else
    col = Menu.info.text_color;

  Cursor.End();
  OutLine(y, no, col, st, _TRUE, do_refresh);
  set_MENCURSOR(&Menu.mencursor);
}

void _PopUp::OutPage(_UWORD actpos, _BOOL do_refresh)
{
  _UWORD  i, j;
  _REGION actreg, ioreg=NULL, newreg=NULL;
  _COLOR  color, c;

  Cursor.End();

//  actreg = ActivateAndRegion(&ioreg, &newreg, &Menu.calcul.scroll_room, T_SOLID|T_COPY);
  actreg = ActivateAndRegion(&ioreg, &newreg, &Menu.calcul.scroll_room);
  color  = GetBackColor_Makro(Menu.info.text_color);
  if(Menu.info.frametype < _THEMEFRAME)
  {
    Bar(Menu.calcul.scroll_room.xy1.x, Menu.calcul.scroll_room.xy1.y, Menu.calcul.scroll_room.xy2.x, Menu.calcul.scroll_room.xy2.y, Menu.info.attrib, MakeColor_Makro(color, color));
  }
  else
  {
    c = MakeColor_Makro(color, color);
    DrawButton(&Menu.calcul.out_room, Menu.info.attrib, Menu.info.frametype, c, c);
  }

//  DrawBackground(_FALSE);
  DeactivateAndRegion(actreg, &ioreg, &newreg);

  if(Menu.position.no > 0)
  {
    j = actpos - Menu.position.begin;
    if(j < Menu.position.height)
      Beam(j, actpos, _TRUE, _FALSE);
  }
  else
  {
    actpos = 0xFFFF;
  }

  j = Menu.position.begin;
  for(i=0; i<Menu.position.height; i++, j++)
  {
    if(j != actpos)
      OutLine(i, j, Menu.info.text_color, _FALSE, _FALSE, _FALSE);
  }

 #ifdef UC_ROTATE
  if(do_refresh == _TRUE)
    RefreshRectangle(&Menu.calcul.scroll_room);
 #endif
}

void _PopUp::DrawBackground(_BOOL shadowstate)
{
  _CHAR *title = NULL;

//  if(Menu.info.Title.GetNo() > 0)
//    title = Menu.info.Title.GetText(0);

  draw_window(&Menu, title, (shadowstate == _TRUE)? P_Window->GetShadow():_FALSE);
}

void _PopUp::Draw(void)
{
  DrawBackground(_TRUE);
  OutPage(Menu.position.pos, _FALSE);
 #ifdef UC_ROTATE
  RefreshRectangle(&Menu.calcul.out_room);
 #endif


}

void _PopUp::DoPositions(_EVENT *pe)
{
  _UWORD     oldpos   = Menu.position.oldpos;
  _UWORD     oldbegin = Menu.position.oldbegin;
  _POSRESULT st;

  if(Menu.position.no > 0)
  {
	 st = calculate_position(&Menu.position, NULL, pe, NULL);
    if(st != P_NOP)
    {
     #ifdef UC_HICOLOR
      switch(st)
      {
        case P_SCROLLUP   :
        case P_SCROLLDOWN :
        case P_REDRAW     : OutPage(Menu.position.pos, _TRUE);
                            break;
        default           : Beam(oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                            Beam(Menu.position.pos-Menu.position.begin, Menu.position.pos, _TRUE, _TRUE); // on
                            break;
      }
     #else
      switch(st)
      {
        case P_SCROLLUP   : Beam(oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                            ScrollUp();
                            Beam(Menu.position.pos-Menu.position.begin, Menu.position.pos, _TRUE, _TRUE); // on
                            break;
        case P_SCROLLDOWN : Beam(oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                            ScrollDown();
                            Beam(Menu.position.pos-Menu.position.begin, Menu.position.pos, _TRUE, _TRUE); // on
                            break;
        case P_REDRAW     : OutPage(Menu.position.pos, _TRUE);
                            break;
        default           : Beam(oldpos-oldbegin, oldpos, _FALSE, _TRUE); // off
                            Beam(Menu.position.pos-Menu.position.begin, Menu.position.pos, _TRUE, _TRUE); // on
                            break;
      }
     #endif
    }
  }


}

void _PopUp::ScrollUp(void)
{
  _ROOM  tmp, room;
  _KOORD h;
  _COLOR color;

  GetLinePosition(0, &tmp);
  h           = (tmp.xy2.y - tmp.xy1.y) + 1;
  room        = Menu.calcul.scroll_room;
  room.xy1.y += h;

  color = MakeColor_Makro(GetBackColor_Makro(Menu.info.text_color), GetBackColor_Makro(Menu.info.text_color));
 #ifdef UC_MOUSE
  _UWORD hide = IfNecHideMouseCursor(&Menu.calcul.scroll_room);
 #endif
  Scroll(room.xy1.x, room.xy1.y, room.xy2.x+1, room.xy2.y+1, 0, -h ,color);
 #ifdef UC_MOUSE
  IfNecShowMouseCursor(hide);
 #endif
}

void _PopUp::ScrollDown(void)
{
  _ROOM  tmp, room;
  _KOORD h;
  _COLOR color;

  GetLinePosition(0, &tmp);
  h           = (tmp.xy2.y - tmp.xy1.y);
  room        = Menu.calcul.scroll_room;
  room.xy2.y -= h;
  color = MakeColor_Makro(GetBackColor_Makro(Menu.info.text_color), GetBackColor_Makro(Menu.info.text_color));
 #ifdef UC_MOUSE
  _UWORD hide = IfNecHideMouseCursor(&Menu.calcul.scroll_room);
 #endif
  Scroll(room.xy1.x, room.xy1.y, room.xy2.x+1, room.xy2.y, 0, h+1 ,color);
 #ifdef UC_MOUSE
  IfNecShowMouseCursor(hide);
 #endif
}

_BOOL _PopUp::Open(_UWORD no, _Window* pw, _KOORD x, _KOORD y, _VARLABEL *pv, _VARLABEL *ovl, void *pmyio)
{
  _BOOL retcode = _FALSE;

  if(Load(no, pw, pv, ovl, pmyio) == _TRUE)
  {
    Menu.info.xy.x = x;
	  Menu.info.xy.y = y;

	  Calculate();

	  if(pv != NULL)
    {
		  Input = *pv;
    }

	  retcode = _TRUE;
  }

  return(retcode);
}

_BOOL _PopUp::Load(_UWORD no, _Window* pw, _VARLABEL *vl, _VARLABEL *ovl, void *pmyio)
{
  _BOOL     retcode = _FALSE;
  _RESULT   result;
  _VARIABLE variable;
  _LSEMENU  *plsemenu;

  Init();
  P_Window = pw;
  P_MyIo   = pmyio;

  if(popup_call(&Menu, &no) == _FALSE)           // user interface open popup
  {
    plsemenu = MenuList.Get_LSEMENU(no);
    if(plsemenu != NULL)
    {
      if(Memory2((void**)&Menu.pointer.Ptr_LSEMENU, sizeof(_LSEMENU)) != 0)
      {
        init_LSEMENU(Menu.pointer.Ptr_LSEMENU);
        if(copy_MENUINFO(&Menu.info, &plsemenu->info) == _TRUE)
        {
          if(copy_LSEMENU(Menu.pointer.Ptr_LSEMENU, plsemenu) == _TRUE)
          {
            Menu.pointer.PtrLine  = popup_mae_line; // --> to linedraw function
            Menu.pointer.PtrRun   = popup_mae_run;       // --> to run function

            if(ovl != NULL)
            {
              if(valid_VARLABEL(ovl) == _TRUE)
              {
                overload_LSEMENU(Menu.pointer.Ptr_LSEMENU, ovl);
                ImOverloaded = *ovl;
              }
            }

            Menu.position.no = MenuList.CalculateLines(Menu.pointer.Ptr_LSEMENU);

            if(vl != NULL)
            {
              if(VarList.GetSystemData(&result, &variable, vl, _TRUE, _TRUE) == _TRUE)
                Menu.position.pos = MenuList.AktLineNo(result.value, Menu.pointer.Ptr_LSEMENU);
            }
            else if((vl == NULL) && (chk_VARLABEL(&Menu.info.server)))
            {
              if(VarList.GetSystemData(&result, &variable, &Menu.info.server, _TRUE, _TRUE) == _TRUE)
              {
                Menu.position.pos = MenuList.AktLineNo(result.value, Menu.pointer.Ptr_LSEMENU);
                copy_VARLABEL(&Input, &Menu.info.server);
              }
            }

            retcode = _TRUE;
          }
        }
      }
    }
   #ifdef OK_DIAGNOSTIC
    else
    {
      retcode = Diagnostic(&Menu, vl, no);
    }
   #endif
  }
  else
  {
    retcode = _TRUE;
  }

  if(retcode == _TRUE)
  {
    Calculate();
  }
  else
  {
    Free();
  }

  return(retcode);
}

void _PopUp::PopUpAddRegion(void)
{
  _ROOM room;

 #ifdef UC_THEME
  if(Menu.info.frametype >= _THEMEFRAME)
    clip_THEME(&Menu.calcul.out_room, Menu.info.frametype);
  else
 #endif
    AddRegion(&Menu.calcul.out_room);

  if(P_Window->GetShadow() == _TRUE)
  {
    room = Menu.calcul.out_room;
    GetShadowRoom(&room);
   #ifdef UC_THEME
    if(Menu.info.frametype >= _THEMEFRAME)
      clip_THEME(&room, Menu.info.frametype);
    else
   #endif
    AddRegion(&room);
  }
}

void _PopUp::StartIntern(_BOOL firsttime)
{
  if((Menu.pointer.PtrStart != NULL) && (P_Window != NULL))
	 Menu.pointer.PtrStart(P_Window, this, firsttime);
}

void _PopUp::ReadyIntern(_BOOL firsttime)
{
//  if(P_Window != NULL)
//    P_Window->Ready(firsttime); 

  if((Menu.pointer.PtrReady != NULL) && (P_Window != NULL))
    Menu.pointer.PtrReady(P_Window, this, firsttime); 
}

void _PopUp::End(void)
{
  Cursor.End();
  if((Menu.pointer.PtrEnd != NULL) && (P_Window != NULL))
	  Menu.pointer.PtrEnd(P_Window, this);
}

void _PopUp::Run(_EVENT *pe)
{
  _ROOM       room;
  _Picture    *pPic = NULL;
  _Window     *pWin;
  _MY_PICTURE *pMyPic;


  if(SetUp.GetHotkeysInMenu() == _TRUE)
  {
    if((pe->ftype == _EVENT_KEYPRESS) || (pe->ftype == _EVENT_KEYRELEASE))
    {
      if(P_Window != NULL)
      {
        pWin = P_Window;

        while((pPic == NULL) && (pWin != NULL))
        {
          pPic = pWin->GetP_Picture();
          if(pPic == NULL)
            pWin = pWin->GetP_Background();
        }

        if(pPic != NULL)
          pMyPic = pPic->GetMyPicture();

        if(pMyPic != NULL)
        {
          if(pMyPic->No > 0)
            pMyPic->Ptr[pMyPic->No-1].DoKeyboard(pe, pWin, pMyPic->GlobalHotkeys);

        }
      }
    }
  }


 #ifdef HID
  track_HID_SCROLL(pe, &Menu.calcul.level, &Menu.position, &Menu.calcul.scroll_room, Menu.info.line_height);
 #endif

 #ifdef OK_SUBLIST
  if((Menu.pointer.PtrSubList != NULL)&&(P_Window != NULL))
    sublist_run(P_Window, this, pe);
  else
 #endif

  if((Menu.pointer.PtrRun != NULL) && (P_Window != NULL))
    Menu.pointer.PtrRun(P_Window, this, pe);

  if(ask_MENCURSOR(&Menu.mencursor) == _TRUE)
  {
    GetLinePosition(Menu.position.pos- Menu.position.begin, &room);
    Cursor.Set(&room, SetUp.GetEditColorCursor(_EDITACTIVE), 0);
  }

  DoPositions(pe);

  level_run(&Menu.calcul.level, Menu.position.no, Menu.position.pos, _FALSE, NULL, Menu.info.frametype);
}

void _PopUp::OutLine(_UWORD y, _UWORD no, _COLOR color, _BOOL beam, _BOOL background, _BOOL do_refresh)
{
  _ROOM   r;
  _REGION actreg, ioreg=NULL, newreg=NULL;

  Font.Set(Menu.info.font, &Menu.info.attrib);
  GetLinePosition(y, &r);

//  actreg = ActivateAndRegion(&ioreg, &newreg, &r, T_COPY|T_SOLID);
  actreg = ActivateAndRegion(&ioreg, &newreg, &r);

 #ifdef UC_MOUSE
  _UWORD hide = IfNecHideMouseCursor(&r);
 #endif

  Cursor.Hide();
 #ifdef OK_SUBLIST
  if((Menu.pointer.PtrSubList != NULL) && (P_Window != NULL))
    sublist_line(P_Window, this, no, &r, color, background);
  else
 #endif
  if((Menu.pointer.PtrLine != NULL) && (P_Window != NULL))
    Menu.pointer.PtrLine(P_Window, this, no, &r, color, background);
  else
    Bar(r.xy1.x, r.xy1.y, r.xy2.x, r.xy2.y, T_COPY|T_SOLID, InvertColor_Makro(color));

 #ifdef UC_ROTATE
  if(do_refresh == _TRUE)
    RefreshRectangle(&r);
 #endif
 #ifdef UC_MOUSE
  IfNecShowMouseCursor(hide);
 #endif

  DeactivateAndRegion(actreg, &ioreg, &newreg);
}

void _PopUp::GetSubPosition(_KOORD *x, _KOORD *y)
{
  _ROOM room;

  // berechne position für sub-popup-menue

  GetLinePosition(Menu.position.pos-Menu.position.begin, &room);
  *y = room.xy1.y;
  *x = Menu.calcul.out_room.xy2.x + 1;
}

void calculate_window(_MENUCALCUL *pc, _MENUINFO *pm, _POSITION *pp, _MENUPOINTER *poi)
{
  _ROOM  room;
  _KOORD corr;
  _UWORD title;
//  _CHAR  *txt;
  _COLOR tcol;

  free_MENUCALCUL(pc);
  pp->height         = pm->height;
  pp->width          = pm->width;
  pc->out_room.xy1.x = pm->xy.x;
  pc->out_room.xy1.y = pm->xy.y;

	title = 0;
//  if(pm->Title.GetNo() > 0)
//  {
//    txt = pm->Title.GetText(0);
//    if(txt != NULL)
//    {
//      if(StrLen(txt, sizeof(_CHAR)) != 0)
//      {
//        title = pm->line_height + 2;
//      }
//    }
//  }

  if(pm->frametype < _THEMEFRAME)
  {
	  pc->scroll_room.xy1.x = pc->out_room.xy1.x + 4;
	  pc->scroll_room.xy1.y = pc->out_room.xy1.y + 4 + title;
	  pc->scroll_room.xy2.x = pc->scroll_room.xy1.x + pm->width;
	  pc->scroll_room.xy2.y = pc->scroll_room.xy1.y + pm->height * pm->line_height - 1;

	  pc->level.room.xy1.x  = pc->scroll_room.xy2.x + 1;
	  pc->level.room.xy1.y  = pc->scroll_room.xy1.y - 1;
	  pc->level.room.xy2.x  = pc->level.room.xy1.x + LEVELBUTTON_WIDTH;
	  pc->level.room.xy2.y  = pc->scroll_room.xy2.y + 1;
  }
  else
  {
	  pc->scroll_room.xy1.x = pc->out_room.xy1.x;
	  pc->scroll_room.xy1.y = pc->out_room.xy1.y + title;
	  pc->scroll_room.xy2.x = pc->scroll_room.xy1.x + pm->width;
	  pc->scroll_room.xy2.y = pc->scroll_room.xy1.y + pm->height * pm->line_height - 1;

	  pc->level.room.xy1.x  = pc->scroll_room.xy2.x + 1;
	  pc->level.room.xy1.y  = pc->scroll_room.xy1.y;
	  pc->level.room.xy2.x  = pc->level.room.xy1.x + LEVELBUTTON_WIDTH;
	  pc->level.room.xy2.y  = pc->scroll_room.xy2.y;
  }

  tcol                  = GetBackColor_Makro(pm->text_color);
	pc->level.color       = MakeColor_Makro(tcol, tcol); //pm->text_color;
	pc->level.frame_color = pm->frame_color;

	if((pp->no > pm->height)||(poi->PtrSubList != NULL)||(poi->Level == _TRUE))
	{
    pc->level.active    = _TRUE;
	}
	else
	{
    pc->level.active      = _FALSE;
    pc->level.room.xy2.x  = pc->level.room.xy1.x;
	}

  if(pm->frametype < _THEMEFRAME)
  {
	  pc->out_room.xy2.x = pc->level.room.xy2.x + 3;
	  pc->out_room.xy2.y = pc->level.room.xy2.y + 3;
  }
  else
  {
	  pc->out_room.xy2.x = pc->level.room.xy2.x;
	  pc->out_room.xy2.y = pc->level.room.xy2.y;
  }

  pc->out_room.xy2.y += pm->basement;

	MyGetScreenSize(&room);
#ifdef ZOOM_KM
 room.xy2.y -= SOFTKEY_NEG_OFF_X;
#endif
	room.xy2.y -= (SetUp.GetSoftkeyHeight() + POPUP_SHADOW);
	room.xy2.x -= POPUP_SHADOW;

	if(pc->out_room.xy2.x > room.xy2.x)
	{
    corr = pc->out_room.xy2.x - room.xy2.x;
    pc->out_room.xy1.x    -= corr;
    pc->out_room.xy2.x    -= corr;
    pc->scroll_room.xy1.x -= corr;
    pc->scroll_room.xy2.x -= corr;
    pc->level.room.xy1.x  -= corr;
    pc->level.room.xy2.x  -= corr;
    pm->xy.x              -= corr;
  }

  if(pc->out_room.xy2.y > room.xy2.y)
  {
    corr = pc->out_room.xy2.y - room.xy2.y;
    pc->out_room.xy1.y    -= corr;
    pc->out_room.xy2.y    -= corr;
    pc->scroll_room.xy1.y -= corr;
    pc->scroll_room.xy2.y -= corr;
    pc->level.room.xy1.y  -= corr;
    pc->level.room.xy2.y  -= corr;
    pm->xy.y              -= corr;
  }
}

void draw_window(_MENU *pm, _CHAR *title, _BOOL shadow)
{
  _COLOR      coltxt, colframe, colback;
  _ROOM       room;
  _MENUCALCUL *pc = &pm->calcul;
  _COLOR      col = InvertColor_Makro(pm->info.text_color);

 #ifdef UC_MOUSE
  _UWORD hide = IfNecHideMouseCursor(&pc->out_room);
 #endif

  if(shadow == _TRUE)
    DrawShadow(pc->out_room, pm->info.frametype);

  DrawButton(&pc->out_room, pm->info.attrib, (pm->info.frametype < _THEMEFRAME)? _3DFRAME : pm->info.frametype, col, InvertColor_Makro(pm->info.frame_color));
 #ifdef UC_ROTATE
  RefreshRectangle(&pc->out_room);
 #endif


  room = pc->scroll_room;
  room.xy1.x --;
  room.xy1.y --;
  room.xy2.x ++;
  room.xy2.y ++;

  if(pm->info.frametype < _THEMEFRAME)
    DrawButton(&room, T_SOLID|T_FILL|T_COPY, _3DFRAME, col, pm->info.frame_color);

  if(DrawBackGround == 0)
  {
    level_draw(&pc->level, _FALSE, _TRUE, NULL, pm->info.frametype);
    level_run(&pc->level, 0, 0, _FALSE, NULL, pm->info.frametype);
  }
  else
  {
    level_draw(&pc->level, _FALSE, _FALSE, NULL, pm->info.frametype);
    level_run(&pc->level, pm->position.no, pm->position.pos, _FALSE, NULL, pm->info.frametype);
  }

  if(title != NULL)
  {
    if(StrLen(title, sizeof(_CHAR)) != 0)
    {
      room.xy1.x = pc->out_room.xy1.x + 1;
      room.xy2.x = pc->out_room.xy2.x - 1;
      room.xy1.y = pc->out_room.xy1.y + 1;
      room.xy2.x = pc->scroll_room.xy1.x - 2;

      coltxt   = MakeColor_Makro(INVISIBLE, pm->info.text_color);
      colback  = MakeColor_Makro(GetBackColor_Makro(pm->info.text_color), GetBackColor_Makro(pm->info.text_color));
      colframe = MakeColor_Makro(INVISIBLE, INVISIBLE);
      OutMultiTextAlign(title, 0, &room, pm->info.font, T_COPY|T_SOLID|T_MIDBOUND|T_CENTERBOUND, _DEFFRAME, coltxt, colback, colframe, sizeof(_CHAR));
    }
  }

 #ifdef UC_MOUSE
  IfNecShowMouseCursor(hide);
 #endif
}

_MENU* _PopUp::GetMenu(void)
{
  return(&Menu);
}

void _PopUp::GetSize(_ROOM *pr)
{
  *pr = Menu.calcul.out_room;
}

_VARLABEL* _PopUp::GetImOverloaded(void)
{
  return(&ImOverloaded);
}

_VARLABEL* _PopUp::GetInput(void)
{
  return(&Input);
}

void* _PopUp::GetP_MyIo(void)
{
  return P_MyIo;
}

void _PopUp::OutBasement(_KOORD x, _UWORD width, _ASCII *txt, _COLOR col)
{
  _ROOM room;

  if(Menu.info.basement > 0)
  {
    room.xy1.x = Menu.calcul.scroll_room.xy1.x;
    room.xy2.x = Menu.calcul.scroll_room.xy2.x;
    room.xy1.y = Menu.calcul.scroll_room.xy2.y + 3;
    room.xy2.y = Menu.calcul.out_room.xy2.y - 2;
    room.xy1.x += x;
	if(width > 1)
      room.xy2.x = room.xy1.x + width - 1;
    OutMultiTextAlign(txt, 0, &room, Menu.info.font, T_COPY|T_SOLID|T_PROP|T_LEFTBOUND|T_MIDBOUND, _DEFFRAME, GetPenColor_Makro(col), GetBackColor_Makro(col), MakeColor_Makro(INVISIBLE, INVISIBLE), sizeof(_ASCII));
   #ifdef UC_ROTATE
    RefreshRectangle(&room);
   #endif
  }
}
