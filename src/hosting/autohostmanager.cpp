/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

#include "autohostmanager.h"

#include "ibattle.h"
#include "user.h"
#include "mainwindow.h"
#include "utils/conversion.h"

AutohostHandler::AutohostHandler():m_battle(0)
{
}

AutohostHandler::~AutohostHandler()
{

}

void AutohostHandler::SetBattle(IBattle* battle)
{
    m_battle=battle;
}

//========================
//-------- Springie ------
//========================

SpringieHandler::SpringieHandler():AutohostHandler()
{

}

SpringieHandler::~SpringieHandler()
{

}

void SpringieHandler::Balance()
{
    m_battle->Say("!balance");
}

void SpringieHandler::SetRandomMap()
{
    m_battle->Say("!map");
}

void SpringieHandler::SetMap(const wxString& map)
{
    m_battle->Say("!map " + STD_STRING(map));
}

void SpringieHandler::ClearStartBoxes()
{
    m_battle->Say("!clear"); /// will check
}

void SpringieHandler::AddStartBox(int posx,int posy,int w,int h)
{
    m_battle->Say(STD_STRING(wxString::Format(wxT("!addbox %i %i %i %i"),posx,posy,w,h)));
}

void SpringieHandler::Notify()
{
    m_battle->Say("!notify");
}

void SpringieHandler::Start()
{
    m_battle->Say("!start");
}

//------------------------------

//========================
//-------- Spads ---------
//========================
SpadsHandler::SpadsHandler():AutohostHandler()
{

}

SpadsHandler::~SpadsHandler()
{

}

void SpadsHandler::Balance()
{
    m_battle->Say("!balance");
}

void SpadsHandler::SetRandomMap()
{
    m_battle->Say("!map 1"); //not so random
}

void SpadsHandler::SetMap(const wxString& map)
{
    m_battle->Say("!map "+STD_STRING(map));
}

void SpadsHandler::ClearStartBoxes()
{

}

void SpadsHandler::AddStartBox(int /*posx*/,int /*posy*/,int /*w*/,int /*h*/)
{

}

void SpadsHandler::Notify()
{
    m_battle->Say("!notify");
}

void SpadsHandler::Start()
{
    m_battle->Say("!start");
}
//-------------


AutohostManager::AutohostManager():m_type(AUTOHOSTTYPE_NONE), m_battle(0)
{

}

AutohostManager::~AutohostManager()
{

}

void AutohostManager::SetBattle(IBattle* battle)
{
    m_battle=battle;
    m_springie.SetBattle(battle);
    m_spads.SetBattle(battle);
    m_emptyhandler.SetBattle(battle);
    m_type=AutohostManager::AUTOHOSTTYPE_NONE;
}

AutohostHandler& AutohostManager::GetAutohostHandler()
{
    switch(m_type)
    {
        case AUTOHOSTTYPE_SPRINGIE:
            return GetSpringie();
        case AUTOHOSTTYPE_SPADS:
            return GetSpads();
		case AUTOHOSTTYPE_NONE:
		case AUTOHOSTTYPE_UNKNOWN:
			return m_emptyhandler;
    }
    return m_emptyhandler;
}

SpringieHandler& AutohostManager::GetSpringie()
{
    return m_springie;
}

SpadsHandler& AutohostManager::GetSpads()
{
    return m_spads;
}

bool AutohostManager::RecnognizeAutohost()
{
    m_type=AutohostManager::AUTOHOSTTYPE_UNKNOWN;
    return false;
}

bool AutohostManager::RecnognizeAutohost(const wxString& who, const wxString& message)
{
    if(m_battle)
    {
        User& founder=m_battle->GetFounder();
        UserStatus status=founder.GetStatus();

        if(status.bot)
        {
            wxString nick=TowxString(founder.GetNick());
            if(who.Upper() ==nick.Upper())
            {
                if(message.Find(_T("welcome to Springie"))!=wxNOT_FOUND)
                {
                    m_type=AutohostManager::AUTOHOSTTYPE_SPRINGIE;
                    return true;
                }
                else if(message.Find(_T("welcome to Spads0"))!=wxNOT_FOUND)
                {
                    m_type=AutohostManager::AUTOHOSTTYPE_SPADS;
                    return true;
                }
            }
        }
    }
    m_type=AutohostManager::AUTOHOSTTYPE_UNKNOWN;
    return false;
}

AutohostManager::AutohostType AutohostManager::GetAutohostType()
{
    return m_type;
}
