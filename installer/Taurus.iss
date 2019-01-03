; We use CMake's configure_file command to replace ${VAR_NAME} variables
; with actual values. Note the dollar sign; {VAR_NAME} variables are from
; Inno, the ones with the dollar we define with CMake.

; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
#define TaurusID        "39B382FF-28F5-4B8E-B977-C669D2F272F9"
#define TaurusVersion   "1.0.0"

#define TaurusName      "Taurus�� Lotto Analyzer"
#define TaurusDirName   "Taurus"
#define TaurusRegKeyName "Taurus"
#define TaurusExeName   "Taurus.exe"

#define TaurusPublisher "HyeonHouse, Inc."
#define TaurusCopyRight "Copyright (C) 2019 " + TaurusPublisher
#define TaurusURL       "http://www.HyeonHouse.com"

;#define TaurusLicenseEN "Taurus_license_en.rtf"
#define TaurusLicenseKO "Taurus_license_ko.rtf"
#define TaurusIcon      "Taurus.ico"
#define TaurusImage     "Taurus_install_image.bmp"
#define TaurusSmallImage "Taurus_install_image_small.bmp"
#define TaurusOutputDir "..\installer"

[Setup]
AppId={#TaurusID}
AppVersion={#TaurusVersion}
VersionInfoVersion={#TaurusVersion}

AppName={#TaurusName}
AppVerName={#TaurusName} {#TaurusVersion}
DefaultDirName={pf}\{#TaurusDirName}
DefaultGroupName={#TaurusDirName}

AppCopyright={#TaurusCopyRight}
AppPublisher={#TaurusPublisher}
AppPublisherURL={#TaurusURL}
AppSupportURL={#TaurusURL}
AppUpdatesURL={#TaurusURL}

UninstallDisplayIcon={app}\{#TaurusExeName}

;LicenseFile=${LICENSE_LOCATION}
;LicenseFile={#TaurusLicense}
SetupIconFile={#TaurusIcon} 
;WizardImageFile ��ġ�� ù ȭ�� ������ ǥ�õǴ� ū �׸� BMP 164x314
;WizardImageFile=compiler:wizmodernimage-IS.bmp
WizardImageFile={#TaurusImage}
;WizardSmallImageFile ��ġ �� ���� ��ܿ� ǥ�õǴ� ���� �׸� BMP 55x58
;WizardSmallImageFile=compiler:wizmodernsmallimage-IS.bmp
WizardSmallImageFile={#TaurusSmallImage}

OutputDir={#TaurusOutputDir}
;OutputBaseFilename=Sigil-${SIGIL_FULL_VERSION}-Windows${ISS_SETUP_FILENAME_PLATFORM}-Setup
OutputBaseFilename={#TaurusDirName}-{#TaurusVersion}-Windows-Setup

AllowNoIcons=yes
ChangesAssociations=yes
Compression=lzma2/ultra
DisableWelcomePage=no
; WinXP is the lowest supported version
MinVersion=0,6.0
PrivilegesRequired=admin
SolidCompression=yes

; "ArchitecturesAllowed=x64" specifies that Setup cannot run on
; anything but x64.
; The ${ISS_ARCH} var is substituted with "x64" or an empty string
ArchitecturesAllowed=""
; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; The ${ISS_ARCH} var is substituted with "x64" or an empty string
ArchitecturesInstallIn64BitMode=""

[Languages]
;Name: "english"; MessagesFile: "compiler:Default.isl"; LicenseFile: {#TaurusLicenseKO}
Name: "korean"; MessagesFile: "compiler:Languages/Korean.isl"; LicenseFile: {#TaurusLicenseKO}

[CustomMessages]
UninstallOldVersion=Undefined //just in case (should be equal to English)
;english.UninstallOldVersion=There are already installed applications. Are you sure?
korean.UninstallOldVersion=������ ��ġ�� ���ø����̼��� �ֽ��ϴ�. ���� �� ����Ͻðڽ��ϱ�?

[Files]
Source: "Taurus\*"; DestDir: "{app}"; Flags: createallsubdirs recursesubdirs ignoreversion
;Source: vendor\vcredist2010.exe; DestDir: {tmp}
Source: vendor\vcredist2013.exe; DestDir: {tmp}
;Source: vendor\vcredist2015.exe; DestDir: {tmp}
;Source: postinstall\postinstall.bat; DestDir: {tmp}

[Components]
; Main files cannot be unchecked. Doesn't do anything, just here for show
Name: main; Description: "Taurus"; Types: full compact custom; Flags: fixed
; Desktop icon.
Name: dicon; Description: "Create a desktop icon"; Types: full custom
Name: dicon\common; Description: "For all users"; Types: full custom; Flags: exclusive
Name: dicon\user; Description: "For the current user only"; Flags: exclusive
; File associations
;Name: afiles; Description: "Associate ebook files with VPEditor"
;Name: afiles\epub; Description: "EPUB"

[Registry]
; Add VPEditor as a global file handler for EPUB and HTML.
;Root: HKLM; Subkey: "Software\Classes\.epub\OpenWithList\{#TaurusExeName}"; Flags: uninsdeletekey
;Root: HKLM; Subkey: "Software\Classes\.htm\OpenWithList\{#TaurusExeName}"; Flags: uninsdeletekey
;Root: HKLM; Subkey: "Software\Classes\.html\OpenWithList\{#TaurusExeName}"; Flags: uninsdeletekey
;Root: HKLM; Subkey: "Software\Classes\.xhtml\OpenWithList\{#TaurusExeName}"; Flags: uninsdeletekey
; Associate EPUB files if requested.
;Components: afiles\epub; Root: HKCR; Subkey: ".epub"; ValueType: string; ValueName: ""; ValueData: "{#TaurusRegKeyName}"; Flags: uninsdeletevalue uninsdeletekeyifempty
;Components: afiles\epub; Root: HKCR; Subkey: "{#TaurusRegKeyName}"; ValueType: string; ValueName: ""; ValueData: "EPUB"; Flags: uninsdeletekey
;Components: afiles\epub; Root: HKCR; Subkey: "{#TaurusRegKeyName}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#TaurusExeName},0"; Flags: uninsdeletekey
;Components: afiles\epub; Root: HKCR; Subkey: "{#TaurusRegKeyName}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#TaurusExeName}"" ""%1"""; Flags: uninsdeletekey

[Icons]
Name: "{group}\{#TaurusDirName}"; Filename: "{app}\{#TaurusExeName}"; IconFilename: "{app}\{#TaurusExeName}"
Name: "{group}\Uninstall {#TaurusDirName}"; Filename: "{uninstallexe}"
; Optional desktop icon.
Components: dicon\common; Name: "{commondesktop}\{#TaurusDirName}"; Filename: "{app}\{#TaurusExeName}"; IconFilename: "{app}\{#TaurusExeName}"
Components: dicon\user; Name: "{userdesktop}\{#TaurusDirName}"; Filename: "{app}\{#TaurusExeName}"; IconFilename: "{app}\{#TaurusExeName}"

[Run]
;Filename: {tmp}\postinstall.bat; Parameters: """{app}\Python3\pyvenv.cfg"" ""{app}\Python3"""; StatusMsg: Configuring pyvenv.cfg file...
;Filename: {tmp}\vcredist2010.exe; Parameters: "/passive /Q:a /c:""msiexec /qb /i vcredist2010.msi"" "; StatusMsg: Checking for 2010 RunTime for Python...
;Filename: {tmp}\vcredist2013.exe; Parameters: "/passive /Q:a /c:""msiexec /qb /i vcredist2013.msi"" "; StatusMsg: Checking for 2013 RunTime for VPEditor...
; The following two commands have the ability to detect whether or not c++ runtimes need to be installed.
;Filename: {tmp}\vcredist2010.exe; Check: VCRedistNeeds2010Install; Parameters: "/passive /Q:a /c:""msiexec /qb /i vcredist2010.msi"" "; StatusMsg: Checking for 2010 RunTime for Python...
Filename: {tmp}\vcredist2013.exe; Check: VCRedistNeeds2013Install; Parameters: "/passive /Q:a /c:""msiexec /qb /i vcredist2013.msi"" "; StatusMsg: Checking for 2013 RunTime for VPEditor...
;Filename: {tmp}\vcredist2015.exe; Check: VCRedistNeeds2015Install; Parameters: "/passive /Q:a /c:""msiexec /qb /i vcredist2015.msi"" "; StatusMsg: Checking for 2015 RunTime for VPEditor...

[Code]
#IFDEF UNICODE
  #DEFINE AW "W"
#ELSE
  #DEFINE AW "A"
#ENDIF
type
  INSTALLSTATE = Longint;
const
  INSTALLSTATE_INVALIDARG = -2;  // An invalid parameter was passed to the function.
  INSTALLSTATE_UNKNOWN = -1;     // The product is neither advertised or installed.
  INSTALLSTATE_ADVERTISED = 1;   // The product is advertised but not installed.
  INSTALLSTATE_ABSENT = 2;       // The product is installed for a different user.
  INSTALLSTATE_DEFAULT = 5;      // The product is installed for the current user.

  // Visual C++ 2010 Redistributable
  VC_2010_REDIST_X86 = '{196BB40D-1578-3D01-B289-BEFC77A11A1E}';
  VC_2010_REDIST_X64 = '{DA5E371C-6333-3D8A-93A4-6FD5B20BCC6E}';
  VC_2010_SP1_REDIST_X86 = '{F0C3E5D1-1ADE-321E-8167-68EF0DE699A5}';
  VC_2010_SP1_REDIST_X64 = '{1D8E6291-B0D5-35EC-8441-6616F567A0F7}';

  // Visual C++ 2013 Redistributable 12.0.21005
  VC_2013_REDIST_X86_MIN = '{13A4EE12-23EA-3371-91EE-EFB36DDFFF3E}';
  VC_2013_REDIST_X64_MIN = '{A749D8E6-B613-3BE3-8F5F-045C84EBA29B}';
  // Microsoft Visual C++ 2013 Additional Runtime - 11.0.61030.0
  VC_2013_REDIST_X86_ADD = '{F8CFEB22-A2E7-3971-9EDA-4B11EDEFC185}';
  VC_2013_REDIST_X64_ADD = '{929FBD26-9020-399B-9A7A-751D61F0B942}';

  // Visual C++ 2015 Redistributable 14.0.23026
  VC_2015_REDIST_X86_MIN = '{A2563E55-3BEC-3828-8D67-E5E8B9E8B675}';
  VC_2015_REDIST_X64_MIN = '{0D3E9E15-DE7A-300B-96F1-B4AF12B96488}';
  // Microsoft Visual C++ 2015 Additional Runtime - 11.0.61030.0
  VC_2015_REDIST_X86_ADD = '{BE960C1C-7BAD-3DE6-8B1A-2616FE532845}';
  VC_2015_REDIST_X64_ADD = '{BC958BD2-5DAC-3862-BB1A-C1BE0790438D}';

function MsiQueryProductState(szProduct: string): INSTALLSTATE;
  external 'MsiQueryProductState{#AW}@msi.dll stdcall';

function VCVersionInstalled(const ProductID: string): Boolean;
begin
  Result := MsiQueryProductState(ProductID) = INSTALLSTATE_DEFAULT;
end;

function VCRedistNeeds2010Install: Boolean;
begin
  // here the Result must be True when you need to install your VCRedist
  // or False when you don't need to, so now it's upon you how you build
  // this statement, the following won't install your VC redist only when
  // the Visual C++ 2010 Redist and Visual C++ 2010 SP1 Redist are
  // installed for the current user

  // Checking to see if VC++ 2010 sp1 redistributable is installed
  if Is64BitInstallMode then
    Result := not (VCVersionInstalled(VC_2010_REDIST_X64) or VCVersionInstalled(VC_2010_SP1_REDIST_X64))
  else
    Result := not (VCVersionInstalled(VC_2010_REDIST_X86) or VCVersionInstalled(VC_2010_SP1_REDIST_X86));
end;

function VCRedistNeeds2013Install: Boolean;
begin
  // here the Result must be True when you need to install your VCRedist
  // or False when you don't need to, so now it's upon you how you build
  // this statement, the following won't install your VC redist only when
  // the Visual C++ 2013 Redist are installed for the current user

   // Checking to see if VC++ 2013 redistributable is installed
  if Is64BitInstallMode then
    Result := not (VCVersionInstalled(VC_2013_REDIST_X64_MIN))
  else
    Result := not (VCVersionInstalled(VC_2013_REDIST_X86_MIN));
end;

function VCRedistNeeds2015Install: Boolean;
begin
  // here the Result must be True when you need to install your VCRedist
  // or False when you don't need to, so now it's upon you how you build
  // this statement, the following won't install your VC redist only when
  // the Visual C++ 2015 Redist are installed for the current user

   // Checking to see if VC++ 2015 redistributable is installed
  if Is64BitInstallMode then
    Result := not (VCVersionInstalled(VC_2015_REDIST_X64_MIN))
  else
    Result := not (VCVersionInstalled(VC_2015_REDIST_X86_MIN));
end;

/////////////////////////////////////////////////////////////////////
function GetUninstallString(): String;
var
  sUnInstPath: String;
  sUnInstallString: String;
begin
  sUnInstPath := ExpandConstant('Software\Microsoft\Windows\CurrentVersion\Uninstall\{#TaurusID}_is1');
  sUnInstallString := '';
  if not RegQueryStringValue(HKLM, sUnInstPath, 'UninstallString', sUnInstallString) then
    RegQueryStringValue(HKCU, sUnInstPath, 'UninstallString', sUnInstallString);
  Result := sUnInstallString;
end;


/////////////////////////////////////////////////////////////////////
function IsUpgrade(): Boolean;
begin
  Result := (GetUninstallString() <> '');
end;


/////////////////////////////////////////////////////////////////////
function UnInstallOldVersion(): Integer;
var
  sUnInstallString: String;
  iResultCode: Integer;
begin
// Return Values:
// 1 - uninstall string is empty
// 2 - error executing the UnInstallString
// 3 - successfully executed the UnInstallString

  // default return value
  Result := 0;

  // get the uninstall string of the old app
  sUnInstallString := GetUninstallString();
  if sUnInstallString <> '' then begin
    sUnInstallString := RemoveQuotes(sUnInstallString);
    if Exec(sUnInstallString, '/SILENT /NORESTART /SUPPRESSMSGBOXES','', SW_HIDE, ewWaitUntilTerminated, iResultCode) then
      Result := 3
    else
      Result := 2;
  end else
    Result := 1;
end;

/////////////////////////////////////////////////////////////////////
//procedure CurStepChanged(CurStep: TSetupStep);
//begin
//  if (CurStep=ssInstall) then
//  begin
//    if (IsUpgrade()) then
//    begin
//      UnInstallOldVersion();
//    end;
//  end;
//end;

function InitializeSetup(): Boolean;
begin
  if (IsUpgrade()) then
  begin
    // Ask the user a Yes/No question
    if MsgBox(ExpandConstant('{cm:UninstallOldVersion}'), mbConfirmation, MB_YESNO) = IDYES then
    begin
      // user clicked Yes
      UnInstallOldVersion();
    end;
  end;

  Result := True;
end;