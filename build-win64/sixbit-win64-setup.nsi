Name "Sixbit"

RequestExecutionLevel highest
SetCompressor /SOLID lzma
SetDateSave off
Unicode true

# Uncomment these lines when investigating reproducibility errors
#SetCompress off
#SetDatablockOptimize off

# General Symbol Definitions
!define REGKEY "SOFTWARE\sixbit"
!define COMPANY "Sixbit Core"
!define URL https://6bit.dev/

# MUI Symbol Definitions
!define MUI_ICON "/home/ubuntu/6bit/share/pixmaps/sixbit.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "/home/ubuntu/6bit/share/pixmaps/nsis-wizard.bmp"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_HEADERIMAGE_BITMAP "/home/ubuntu/6bit/share/pixmaps/nsis-header.bmp"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Sixbit Core"
!define MUI_FINISHPAGE_RUN "$WINDIR\explorer.exe"
!define MUI_FINISHPAGE_RUN_PARAMETERS $INSTDIR\sixbit-qt.exe
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "/home/ubuntu/6bit/share/pixmaps/nsis-wizard.bmp"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Included files
!include Sections.nsh
!include MUI2.nsh
!include x64.nsh

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
InstallDir $PROGRAMFILES64\Sixbit Core
CRCCheck force
XPStyle on
BrandingText "Sixbit Core Installer"
ShowInstDetails show
VIProductVersion 1.0.0.0
VIAddVersionKey ProductName "Sixbit Core"
VIAddVersionKey ProductVersion "1.0.0"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "1.0.0"
VIAddVersionKey FileDescription "Installer for Sixbit"
VIAddVersionKey LegalCopyright "Copyright (C) 2009-2026 The 6bit developers"
InstallDirRegKey HKCU "${REGKEY}" Path
ShowUninstDetails show

# Installer sections
Section -Main SEC0000
    SetOutPath $INSTDIR
    SetOverwrite on
   
    File /oname=COPYING.txt /home/ubuntu/6bit/COPYING
    File /oname=readme.txt /home/ubuntu/6bit/doc/README_windows.txt
    File /home/ubuntu/6bit/share/examples/sixbit.conf
    SetOutPath $INSTDIR\share\rpcauth
    File /home/ubuntu/6bit/share/rpcauth/*.*

    SetOutPath $INSTDIR
    File /home/ubuntu/6bit/build-win64/release/sixbit-qt.exe
    File /home/ubuntu/6bit/build-win64/release/sixbit.exe
    File /home/ubuntu/6bit/build-win64/release/sixbitd.exe
    File /home/ubuntu/6bit/build-win64/release/sixbit-cli.exe
    File /home/ubuntu/6bit/build-win64/release/sixbit-tx.exe
    File /home/ubuntu/6bit/build-win64/release/sixbit-wallet.exe   

    SetOutPath $INSTDIR
    WriteRegStr HKCU "${REGKEY}\Components" Main 1
SectionEnd

Section -post SEC0001
    WriteRegStr HKCU "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory $SMPROGRAMS\$StartMenuGroup
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Sixbit Core.lnk" $INSTDIR\sixbit-qt.exe
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Sixbit Core (testnet).lnk" "$INSTDIR\sixbit-qt.exe" "-testnet" "$INSTDIR\sixbit-qt.exe" 1
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Sixbit Core (signet).lnk" "$INSTDIR\sixbit-qt.exe" "-signet" "$INSTDIR\sixbit-qt.exe" 2
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Sixbit Core (testnet4).lnk" "$INSTDIR\sixbit-qt.exe" "-testnet4" "$INSTDIR\sixbit-qt.exe" 3
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Uninstall Sixbit Core.lnk" $INSTDIR\uninstall.exe
    CreateShortcut "$DESKTOP\Sixbit Core.lnk" $INSTDIR\sixbit-qt.exe
    !insertmacro MUI_STARTMENU_WRITE_END
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit" DisplayName "Sixbit Core"   
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit" Publisher "${COMPANY}"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit" URLInfoAbout "${URL}"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit" DisplayIcon $INSTDIR\sixbit-qt.exe
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit" NoModify 1
    WriteRegDWORD HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit" NoRepair 1
    WriteRegStr HKCR "sixbit" "URL Protocol" ""
    WriteRegStr HKCR "sixbit" "" "URL:sixbit"
    WriteRegStr HKCR "sixbit\DefaultIcon" "" $INSTDIR\sixbit-qt.exe
    WriteRegStr HKCR "sixbit\shell\open\command" "" '"$INSTDIR\sixbit-qt.exe" "%1"'

    # Lingering since fb2b05b1259d3e69e6e675adfa30b429424c7625 which removed the suffix
    DeleteRegValue HKCU "${REGKEY} (64-bit)\Components" Main
    DeleteRegKey HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) (64-bit)"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name) (64-bit).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\$(^Name) (64-bit).lnk"
    DeleteRegValue HKCU "${REGKEY} (64-bit)" StartMenuGroup
    DeleteRegValue HKCU "${REGKEY} (64-bit)" Path
    DeleteRegKey /IfEmpty HKCU "${REGKEY} (64-bit)\Components"
    DeleteRegKey /IfEmpty HKCU "${REGKEY} (64-bit)"
    Delete $INSTDIR\debug.log
    Delete $INSTDIR\db.log

    # Lingering since 77b2923f87131a407f7d4193c54db22375130403
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Sixbit Core (testnet, 64-bit).lnk"
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKCU "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section /o -un.Main UNSEC0000
    Delete /REBOOTOK $INSTDIR\sixbit.exe
    Delete /REBOOTOK $INSTDIR\sixbit-qt.exe
    Delete /REBOOTOK $INSTDIR\sixbitd.exe
    Delete /REBOOTOK $INSTDIR\sixbit-cli.exe
    Delete /REBOOTOK $INSTDIR\sixbit-tx.exe
    Delete /REBOOTOK $INSTDIR\sixbit-wallet.exe
    Delete /REBOOTOK $INSTDIR\COPYING.txt
    Delete /REBOOTOK $INSTDIR\readme.txt
    Delete /REBOOTOK $INSTDIR\sixbit.conf
    RMDir /r /REBOOTOK $INSTDIR\share
    RMDir /r /REBOOTOK $INSTDIR\daemon
    DeleteRegValue HKCU "${REGKEY}\Components" Main
SectionEnd

Section -un.post UNSEC0001
    DeleteRegKey HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\sixbit"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall Sixbit Core.lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Sixbit Core.lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Sixbit Core (testnet).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Sixbit Core (testnet4).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Sixbit Core (signet).lnk"
    Delete /REBOOTOK "$SMSTARTUP\sixbit.lnk"
    Delete /REBOOTOK $INSTDIR\uninstall.exe
    Delete /REBOOTOK $INSTDIR\debug.log
    Delete /REBOOTOK $INSTDIR\db.log
    DeleteRegValue HKCU "${REGKEY}" StartMenuGroup
    DeleteRegValue HKCU "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKCU "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKCU "${REGKEY}"
    DeleteRegKey HKCR "sixbit"
    RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    RmDir /REBOOTOK $INSTDIR
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd

# Installer functions
Function .onInit
    InitPluginsDir
    ${If} ${RunningX64}
      ; disable registry redirection (enable access to 64-bit portion of registry)
      SetRegView 64
    ${Else}
      MessageBox MB_OK|MB_ICONSTOP "Cannot install 64-bit version on a 32-bit system."
      Abort
    ${EndIf}
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKCU "${REGKEY}" Path
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}
FunctionEnd
