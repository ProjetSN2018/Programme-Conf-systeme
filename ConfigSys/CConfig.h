#pragma once
#include <vector>
#include <fstream>
using namespace std;

#define		PARAM_CLIENT_NAME	0
#define		PARAM_SAS_NAME		1
#define		PARAM_DOOR_NB		2
#define		PARAM_MODE			3
#define		NB_PARAM			4

class CConfig 
{
	friend fstream& operator>> (fstream& is, CConfig& config);
	friend fstream& operator<< (fstream& os, const CConfig& config);

public:
	struct t_param {
		CEdit*			pEDClientName;
		CEdit*			pEDSasName;
		CEdit*			pEDDoorNb;
		CCheckListBox*	pChkAuto;
		CCheckListBox*	pChkSauto;
		CCheckListBox*	pChkManual;
	};

private:
	CString		m_strClientName;
	CString		m_strSASName;
	CString		m_strDoorNb;
	CString		m_strModeAuto;
	CString		m_strModeSauto;
	CString		m_strModeManual;


public:
	CConfig();
	~CConfig();

	void SetConf(CString& ClientName, CString& SASName, CString& DoorNb, CString& ChkAuto, CString& ChkSAuto, CString& ChkManual);
	void Print(t_param& pParam) const;
};