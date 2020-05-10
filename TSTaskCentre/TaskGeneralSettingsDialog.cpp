#include "stdafx.h"
#include "TSTaskCentre.h"
#include "TaskGeneralSettingsDialog.h"
#include "MiscDialog.h"
#include "resource.h"
#include "../Common/DebugDef.h"


namespace TSTaskCentre
{

	CTaskGeneralSettingsDialog::CTaskGeneralSettingsDialog(CTSTaskCentreCore &Core,int PageID,const TSTask::CTSTaskSettings &Settings)
		: CTaskSettingsPage(Core,PageID,Settings)
	{
	}

	CTaskGeneralSettingsDialog::~CTaskGeneralSettingsDialog()
	{
		Destroy();
	}

	bool CTaskGeneralSettingsDialog::Create(HWND hwndOwner,HINSTANCE hinst)
	{
		return CreateDialogWindow(hwndOwner,hinst,MAKEINTRESOURCE(IDD_TASK_SETTINGS_GENERAL));
	}

	INT_PTR CTaskGeneralSettingsDialog::DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		switch (uMsg) {
		case WM_INITDIALOG:
			{
				TSTask::String Text;

				if (m_Settings.BonDriver.GetLoadDirectory(&Text))
					SetItemString(IDC_TASK_SETTINGS_BONDRIVER_FOLDER,Text);

				static const LPCTSTR DescrambleList[] = {
					TEXT("スクランブル解除しない"),
					TEXT("全てのサービスをスクランブル解除する"),
					TEXT("指定されたサービスのみスクランブル解除する"),
				};
				static_assert(_countof(DescrambleList)==TSTask::DESCRAMBLE_TRAILER,
							  "スクランブル解除の設定の数が一致しません。");
				for (int i=0;i<_countof(DescrambleList);i++) {
					::SendDlgItemMessage(hDlg,IDC_TASK_SETTINGS_DESCRAMBLE,CB_ADDSTRING,0,
										 reinterpret_cast<LPARAM>(DescrambleList[i]));
				}
				::SendDlgItemMessage(hDlg,IDC_TASK_SETTINGS_DESCRAMBLE,CB_SETCURSEL,
									 (WPARAM)m_Settings.General.GetDescrambleType(),0);

				CheckItem(IDC_TASK_SETTINGS_EMM_PROCESS,m_Settings.General.GetEMMProcess());

				CheckItem(IDC_TASK_SETTINGS_EXECUTE_CLIENT,m_Settings.General.GetClientExecuteOnStart());
				EnableItems(IDC_TASK_SETTINGS_CLIENT_FILE_NAME_LABEL,
							IDC_TASK_SETTINGS_CLIENT_OPTIONS,
							m_Settings.General.GetClientExecuteOnStart());
				if (m_Settings.General.GetClientFilePath(&Text))
					SetItemString(IDC_TASK_SETTINGS_CLIENT_FILE_NAME,Text);
				if (m_Settings.General.GetClientOptions(&Text))
					SetItemString(IDC_TASK_SETTINGS_CLIENT_OPTIONS,Text);
			}
			return TRUE;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case IDC_TASK_SETTINGS_BONDRIVER_FOLDER_BROWSE:
				{
					TSTask::String Folder;

					GetItemString(IDC_TASK_SETTINGS_BONDRIVER_FOLDER,&Folder);
					if (Folder.empty())
						TSTask::GetModuleDirectory(nullptr,&Folder);
					if (BrowseFolderDialog(hDlg,&Folder,L"BonDriver の検索フォルダ"))
						SetItemString(IDC_TASK_SETTINGS_BONDRIVER_FOLDER,Folder);
				}
				return TRUE;

			case IDC_TASK_SETTINGS_EXECUTE_CLIENT:
				EnableItems(IDC_TASK_SETTINGS_CLIENT_FILE_NAME_LABEL,
							IDC_TASK_SETTINGS_CLIENT_OPTIONS,
							IsItemChecked(IDC_TASK_SETTINGS_EXECUTE_CLIENT));
				return TRUE;
			}
			return TRUE;
		}

		return FALSE;
	}

	bool CTaskGeneralSettingsDialog::OnOK(TSTask::CTSTaskSettings &Settings)
	{
		TSTask::String Text;

		if (GetItemString(IDC_TASK_SETTINGS_BONDRIVER_FOLDER,&Text))
			Settings.BonDriver.SetLoadDirectory(Text);

		Settings.General.SetDescrambleType(TSTask::DescrambleType(
			::SendDlgItemMessage(m_hDlg,IDC_TASK_SETTINGS_DESCRAMBLE,CB_GETCURSEL,0,0)));

		Settings.General.SetEMMProcess(IsItemChecked(IDC_TASK_SETTINGS_EMM_PROCESS));

		Settings.General.SetClientExecuteOnStart(
			IsItemChecked(IDC_TASK_SETTINGS_EXECUTE_CLIENT));
		if (GetItemString(IDC_TASK_SETTINGS_CLIENT_FILE_NAME,&Text))
			Settings.General.SetClientFilePath(Text);
		if (GetItemString(IDC_TASK_SETTINGS_CLIENT_OPTIONS,&Text))
			Settings.General.SetClientOptions(Text);

		return true;
	}

}
