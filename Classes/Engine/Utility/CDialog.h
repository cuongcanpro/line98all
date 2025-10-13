/*
 * CDialog.h
 *
 *  Created on: Jul 23, 2013
 *      Author: kienvn
 */

#ifndef CDIALOG_H_
#define CDIALOG_H_
enum DialogType
{
	DIALOG_CONNECTION_ERROR,
	DIALOG_ASK_EXIT_GAME,
	DIALOG_UPDATE_VERSION,
	DIALOG_MAINTAIN
};
class CDialog {
public:
	static CDialog* shared();
	static void purge();
private:
	static CDialog* _dialog;
public:
	void processDialogCallback(int type, int result);
	void showYesNoDialog(int type,const char* titleTxt, const char* messageTxt, const char* okTxt,const char* noTxt);
	void showDialogConnectionError();
	void showDialogExitGame();
	void showDialogUpdateVersion();
	void showDialogMaintain(const char* msg);
	void showOKDialog(int type, const char* titleTxt,const char* messageTxt, const char* okTxt);
	void showToastWithLongTime(const char* messageTxt);
	void showToastWithShortTime(const char* messageTxt);
	void openLink(const char* link);
	
};

#endif /* CDIALOG_H_ */
