#ifndef __finaco_mainFrame__
#define __finaco_mainFrame__

/**
@file
Subclass of mainFrame, which is generated by wxFormBuilder.
*/
#include "gui.h"

//// end generated include

#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/config.h>
#include <wx/busyinfo.h>
#include "finaco_destination.h"
#include "finaco_about.h"
#include "finaco_searchStatus.h"
#include "finaco_moveStatus.h"
#include "engine.h"
#include "dcm2img.h"
#include <map>

/** Implementing mainFrame */
class finaco_mainFrame : public mainFrame
{
	protected:
		// Handlers for mainFrame events.
		void OnDestinationEdit( wxCommandEvent& event );
		void m_studiesOnListColClick( wxListEvent& event );
		void OnClear( wxCommandEvent& event );
		void OnLoad( wxCommandEvent& event);
		void OnSave( wxCommandEvent& event);
		void OnQuery(wxCommandEvent& event);
		void OnMove( wxCommandEvent& event );
		void OnAbout( wxCommandEvent& event );
		void OnExit( wxCommandEvent& event );
	public:
		/** Constructor */
		finaco_mainFrame( wxWindow* parent );
	//// end generated class members

		~finaco_mainFrame();

		void m_studiesOnListItemChecked(wxListEvent& event);
		void m_studiesOnListItemUnchecked(wxListEvent& event);
		void FillDestinationList();
		void FillStudyList();
		int fillstudiescallback(Study &study);

		engine m_engine;


};

#endif // __finaco_mainFrame__
