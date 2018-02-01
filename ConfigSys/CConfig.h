#include <vector>
#include <fstream>
using namespace std;

class CConfig 
{
	friend fstream& operator>> (fstream& is, CConfig& config);
	friend fstream& operator<< (fstream& os, const CConfig& config);

public:
	struct t_param {
		CEdit*	pEDClientName;
		CEdit*	pEDSasName;
		CEdit*	pEDDoorNb;
	};

private:
	CString		m_strClientName;
	CString		m_strSASName;
	CString		m_strDoorNb;
	CString		m_strChkAuto;
	CString		m_strChkSAuto;
	CString		m_strChkManual;


public:
	CConfig();
	//CConfig(CString& ClientName, CString& SASName, CString& DoorNb);
	~CConfig();

	void SetConf(CString& ClientName, CString& SASName, CString& DoorNb, CString& ChkAuto);


	void Print(t_param& pParam) const;
};