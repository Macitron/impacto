#include "inst_system.h"
#include "inst_controlflow.h"
#include "inst_graphics2d.h"
#include "inst_graphics3d.h"
#include "inst_dialogue.h"
#include "inst_sound.h"
#include "inst_movie.h"
#include "inst_gamespecific.h"
#include "inst_misc.h"

// clang-format off

namespace Impacto {

namespace Vm {

InstructionProc inline constexpr OpcodeTableSystem_CC[256] = {
    InstEnd,                  // 00 00
    InstCreateThread,         // 00 01
    InstKillThread,           // 00 02
    InstReset,                // 00 03
    InstScriptLoad,           // 00 04
    InstWait,                 // 00 05
    InstHalt,                 // 00 06
    InstJump,                 // 00 07
    InstJumpTable,            // 00 08
    InstGetLabelAdr,          // 00 09
    InstIf,                   // 00 0A
    InstCall,                 // 00 0B
    InstJumpFar,              // 00 0C
    InstCallFar,              // 00 0D
    InstReturn,               // 00 0E
    InstLoop,                 // 00 0F
    InstFlagOnJump,           // 00 10
    InstFlagOnWait,           // 00 11
    InstSetFlag,              // 00 12
    InstResetFlag,            // 00 13
    InstCopyFlag,             // 00 14
    InstKeyOnJump,            // 00 15
    InstKeyWait,              // 00 16
    InstKeyWaitTimer,         // 00 17
    InstMemberWrite,          // 00 18
    InstThreadControl,        // 00 19
    InstGetSelfPointer,       // 00 1A
    InstLoadJump,             // 00 1B
    InstVsync,                // 00 1C
    InstTest,                 // 00 1D
    InstThreadControlStore,   // 00 1E
    InstSwitch,               // 00 1F
    InstCase,                 // 00 20
    InstBGMplay,              // 00 21
    InstBGMstop,              // 00 22
    InstSEplay,               // 00 23
    InstSEstop,               // 00 24
    InstPadAct,               // 00 25
    InstSSEplay,              // 00 26
    InstSSEstop,              // 00 27
    InstCopyThreadWork,       // 00 28
    InstUPLmenuUI,            // 00 29
    InstSave,                 // 00 2A
    InstSaveIconLoad,         // 00 2B
    InstBGMflag,              // 00 2C
    InstUPLxTitle,            // 00 2D
    InstPresence,             // 00 2E
    InstSetAchievement,          // 00 2F
    InstSetPlayer,            // 00 30
    InstVoiceTableLoadMaybe,  // 00 31
    InstSetPadCustom,         // 00 32
    InstMwait,                // 00 33
    InstTerminate,            // 00 34
    InstSignIn,               // 00 35
    InstAchievementIcon,      // 00 36
    InstVoicePlay,            // 00 37
    InstVoiceStopNew,         // 00 38
    InstVoicePlayWait,        // 00 39
    InstBGMduelPlay,          // 00 3A
    InstSNDpause,             // 00 3B
    InstSEplayWait,           // 00 3C
    InstDebugPrint,           // 00 3D
    InstResetSoundAll,        // 00 3E
    InstSNDloadStop,          // 00 3F
    InstBGMstopWait,          // 00 40
    InstUnk0041,              // 00 41
    InstSetX360SysMesPos,     // 00 42
    InstSystemMes,            // 00 43
    InstSystemMenu,           // 00 44
    InstGetNowTime,           // 00 45
    InstGetSystemStatus,      // 00 46
    InstReboot,               // 00 47
    InstReloadScript,         // 00 48
    InstReloadScriptMenu,     // 00 49
    InstDebugEditer,          // 00 4A
    InstSysSeload,            // 00 4B
    InstDummy,                // 00 4C
    InstSysVoicePlay,         // 00 4D
    InstPadActEx,             // 00 4E
    InstDebugSetup,           // 00 4F
    InstPressStartNew,        // 00 50
    InstGlobalSystemMessage,  // 00 51
    InstUnk0052,              // 00 52
    InstClickOnJump,          // 00 53
    InstKeyboardOnJump,       // 00 54
    InstControlOnJump,        // 00 55
    InstGetControl,           // 00 56
    InstDummy,                // 00 57
    InstDummy,                // 00 58
    InstDummy,                // 00 59
    InstDummy,                // 00 5A
    InstDummy,                // 00 5B
    InstFlagOffReturn,        // 00 5C
    InstDummy,                // 00 5D
    InstDummy,                // 00 5E
    InstPackFileAddBind,      // 00 5F
    InstDummy,                // 00 60
    InstDummy,                // 00 61
    InstDummy,                // 00 62
    InstDummy,                // 00 63
    InstDummy,                // 00 64
    InstDummy,                // 00 65
    InstDummy,                // 00 66
    InstDummy,                // 00 67
    InstDummy,                // 00 68
    InstDummy,                // 00 69
    InstDummy,                // 00 6A
    InstDummy,                // 00 6B
    InstDummy,                // 00 6C
    InstDummy,                // 00 6D
    InstDummy,                // 00 6E
    InstDummy,                // 00 6F
    InstDummy,                // 00 70
    InstDummy,                // 00 71
    InstDummy,                // 00 72
    InstDummy,                // 00 73
    InstDummy,                // 00 74
    InstDummy,                // 00 75
    InstDummy,                // 00 76
    InstDummy,                // 00 77
    InstDummy,                // 00 78
    InstDummy,                // 00 79
    InstDummy,                // 00 7A
    InstDummy,                // 00 7B
    InstDummy,                // 00 7C
    InstDummy,                // 00 7D
    InstDummy,                // 00 7E
    InstDummy,                // 00 7F
    InstDummy,                // 00 80
    InstDummy,                // 00 81
    InstDummy,                // 00 82
    InstDummy,                // 00 83
    InstDummy,                // 00 84
    InstDummy,                // 00 85
    InstDummy,                // 00 86
    InstDummy,                // 00 87
    InstDummy,                // 00 88
    InstDummy,                // 00 89
    InstDummy,                // 00 8A
    InstDummy,                // 00 8B
    InstDummy,                // 00 8C
    InstDummy,                // 00 8D
    InstDummy,                // 00 8E
    InstDummy,                // 00 8F
    InstDummy,                // 00 90
    InstDummy,                // 00 91
    InstDummy,                // 00 92
    InstDummy,                // 00 93
    InstDummy,                // 00 94
    InstDummy,                // 00 95
    InstDummy,                // 00 96
    InstDummy,                // 00 97
    InstDummy,                // 00 98
    InstDummy,                // 00 99
    InstDummy,                // 00 9A
    InstDummy,                // 00 9B
    InstDummy,                // 00 9C
    InstDummy,                // 00 9D
    InstDummy,                // 00 9E
    InstDummy,                // 00 9F
    InstDummy,                // 00 A0
    InstDummy,                // 00 A1
    InstDummy,                // 00 A2
    InstDummy,                // 00 A3
    InstDummy,                // 00 A4
    InstDummy,                // 00 A5
    InstDummy,                // 00 A6
    InstDummy,                // 00 A7
    InstDummy,                // 00 A8
    InstDummy,                // 00 A9
    InstDummy,                // 00 AA
    InstDummy,                // 00 AB
    InstDummy,                // 00 AC
    InstDummy,                // 00 AD
    InstDummy,                // 00 AE
    InstDummy,                // 00 AF
    InstDummy,                // 00 B0
    InstDummy,                // 00 B1
    InstDummy,                // 00 B2
    InstDummy,                // 00 B3
    InstDummy,                // 00 B4
    InstDummy,                // 00 B5
    InstDummy,                // 00 B6
    InstDummy,                // 00 B7
    InstDummy,                // 00 B8
    InstDummy,                // 00 B9
    InstDummy,                // 00 BA
    InstDummy,                // 00 BB
    InstDummy,                // 00 BC
    InstDummy,                // 00 BD
    InstDummy,                // 00 BE
    InstDummy,                // 00 BF
    InstDummy,                // 00 C0
    InstDummy,                // 00 C1
    InstDummy,                // 00 C2
    InstDummy,                // 00 C3
    InstDummy,                // 00 C4
    InstDummy,                // 00 C5
    InstDummy,                // 00 C6
    InstDummy,                // 00 C7
    InstDummy,                // 00 C8
    InstDummy,                // 00 C9
    InstDummy,                // 00 CA
    InstDummy,                // 00 CB
    InstDummy,                // 00 CC
    InstDummy,                // 00 CD
    InstDummy,                // 00 CE
    InstDummy,                // 00 CF
    InstDummy,                // 00 D0
    InstDummy,                // 00 D1
    InstDummy,                // 00 D2
    InstDummy,                // 00 D3
    InstDummy,                // 00 D4
    InstDummy,                // 00 D5
    InstDummy,                // 00 D6
    InstDummy,                // 00 D7
    InstDummy,                // 00 D8
    InstDummy,                // 00 D9
    InstDummy,                // 00 DA
    InstDummy,                // 00 DB
    InstDummy,                // 00 DC
    InstDummy,                // 00 DD
    InstDummy,                // 00 DE
    InstDummy,                // 00 DF
    InstDummy,                // 00 E0
    InstDummy,                // 00 E1
    InstDummy,                // 00 E2
    InstDummy,                // 00 E3
    InstDummy,                // 00 E4
    InstDummy,                // 00 E5
    InstDummy,                // 00 E6
    InstDummy,                // 00 E7
    InstDummy,                // 00 E8
    InstDummy,                // 00 E9
    InstDummy,                // 00 EA
    InstDummy,                // 00 EB
    InstDummy,                // 00 EC
    InstDummy,                // 00 ED
    InstDummy,                // 00 EE
    InstDummy,                // 00 EF
    InstDummy,                // 00 F0
    InstDummy,                // 00 F1
    InstDummy,                // 00 F2
    InstDummy,                // 00 F3
    InstDummy,                // 00 F4
    InstDummy,                // 00 F5
    InstDummy,                // 00 F6
    InstDummy,                // 00 F7
    InstDummy,                // 00 F8
    InstDummy,                // 00 F9
    InstDummy,                // 00 FA
    InstDummy,                // 00 FB
    InstDummy,                // 00 FC
    InstDummy,                // 00 FD
    InstDummy,                // 00 FE
    InstDummy                 // 00 FF
};

InstructionProc inline constexpr OpcodeTableGraph_CC[256] = {
    InstCreateSurf,        // 01 00
    InstReleaseSurf,       // 01 01
    InstLoadPic,           // 01 02
    InstReleaseSurf,       // 01 03
    InstSurfFill,          // 01 04
    InstCalc,              // 01 05
    InstMesViewFlag,       // 01 06
    InstSetMesWinPri,      // 01 07
    InstMesSync,           // 01 08
    InstMesSetID,          // 01 09
    InstMesCls,            // 01 0A
    InstMesVoiceWait,      // 01 0B
    InstMes,               // 01 0C
    InstMesMain,           // 01 0D
    InstSetMesModeFormat,  // 01 0E
    InstSetNGmoji,         // 01 0F
    InstMesRev,            // 01 10
    InstMessWindow,        // 01 11
    InstSel,               // 01 12
    InstSelect,            // 01 13
    InstSysSel,            // 01 14
    InstSysSelect,         // 01 15
    InstDummy,             // 01 16
    InstDummy,             // 01 17
    InstDummy,             // 01 18
    InstDummy,             // 01 19
    InstDummy,             // 01 1A
    InstDummy,             // 01 1B
    InstDummy,             // 01 1C
    InstDummy,             // 01 1D
    InstDummy,             // 01 1E
    InstLoadFontWidths,    // 01 1F
    InstSCcapture,         // 01 20
    InstSetTextTable,      // 01 21
    InstPlayMovie,         // 01 22
    InstMovieMain,         // 01 23
    InstLoadMovie,         // 01 24
    InstSetRevMes,         // 01 25
    InstPlayMovieMemory,   // 01 26
    InstPlayMovie,         // 01 27
    InstMovieMain,         // 01 28
    InstLoadMovie,         // 01 29
    InstPlayMovieMemory,   // 01 2A
    InstSFDpause,          // 01 2B
    InstPlayMovie,         // 01 2C
    InstUnk012D,           // 01 2D
    InstDummy,             // 01 2E
    InstDummy,             // 01 2F
    InstDummy,             // 01 30
    InstDummy,             // 01 31
    InstDummy,             // 01 32
    InstDummy,             // 01 33
    InstDummy,             // 01 34
    InstDummy,             // 01 35
    InstDummy,             // 01 36
    InstDummy,             // 01 37
    InstDummy,             // 01 38
    InstDummy,             // 01 39
    InstDummy,             // 01 3A
    InstDummy,             // 01 3B
    InstDummy,             // 01 3C
    InstDummy,             // 01 3D
    InstDummy,             // 01 3E
    InstDummy,             // 01 3F
    InstDummy,             // 01 40
    InstDummy,             // 01 41
    InstDummy,             // 01 42
    InstDummy,             // 01 43
    InstDummy,             // 01 44
    InstDummy,             // 01 45
    InstDummy,             // 01 46
    InstDummy,             // 01 47
    InstDummy,             // 01 48
    InstDummy,             // 01 49
    InstDummy,             // 01 4A
    InstDummy,             // 01 4B
    InstDummy,             // 01 4C
    InstDummy,             // 01 4D
    InstDummy,             // 01 4E
    InstDummy,             // 01 4F
    InstDummy,             // 01 50
    InstDummy,             // 01 51
    InstDummy,             // 01 52
    InstDummy,             // 01 53
    InstDummy,             // 01 54
    InstDummy,             // 01 55
    InstDummy,             // 01 56
    InstDummy,             // 01 57
    InstDummy,             // 01 58
    InstDummy,             // 01 59
    InstDummy,             // 01 5A
    InstDummy,             // 01 5B
    InstDummy,             // 01 5C
    InstDummy,             // 01 5D
    InstDummy,             // 01 5E
    InstDummy,             // 01 5F
    InstDummy,             // 01 60
    InstDummy,             // 01 61
    InstDummy,             // 01 62
    InstDummy,             // 01 63
    InstDummy,             // 01 64
    InstDummy,             // 01 65
    InstDummy,             // 01 66
    InstDummy,             // 01 67
    InstDummy,             // 01 68
    InstDummy,             // 01 69
    InstDummy,             // 01 6A
    InstDummy,             // 01 6B
    InstDummy,             // 01 6C
    InstDummy,             // 01 6D
    InstDummy,             // 01 6E
    InstDummy,             // 01 6F
    InstDummy,             // 01 70
    InstDummy,             // 01 71
    InstDummy,             // 01 72
    InstDummy,             // 01 73
    InstDummy,             // 01 74
    InstDummy,             // 01 75
    InstDummy,             // 01 76
    InstDummy,             // 01 77
    InstDummy,             // 01 78
    InstDummy,             // 01 79
    InstDummy,             // 01 7A
    InstDummy,             // 01 7B
    InstDummy,             // 01 7C
    InstDummy,             // 01 7D
    InstDummy,             // 01 7E
    InstDummy,             // 01 7F
    InstDummy,             // 01 80
    InstDummy,             // 01 81
    InstDummy,             // 01 82
    InstDummy,             // 01 83
    InstDummy,             // 01 84
    InstDummy,             // 01 85
    InstDummy,             // 01 86
    InstDummy,             // 01 87
    InstDummy,             // 01 88
    InstDummy,             // 01 89
    InstDummy,             // 01 8A
    InstDummy,             // 01 8B
    InstDummy,             // 01 8C
    InstDummy,             // 01 8D
    InstDummy,             // 01 8E
    InstDummy,             // 01 8F
    InstDummy,             // 01 90
    InstDummy,             // 01 91
    InstDummy,             // 01 92
    InstDummy,             // 01 93
    InstDummy,             // 01 94
    InstDummy,             // 01 95
    InstDummy,             // 01 96
    InstDummy,             // 01 97
    InstDummy,             // 01 98
    InstDummy,             // 01 99
    InstDummy,             // 01 9A
    InstDummy,             // 01 9B
    InstDummy,             // 01 9C
    InstDummy,             // 01 9D
    InstDummy,             // 01 9E
    InstDummy,             // 01 9F
    InstDummy,             // 01 A0
    InstDummy,             // 01 A1
    InstDummy,             // 01 A2
    InstDummy,             // 01 A3
    InstDummy,             // 01 A4
    InstDummy,             // 01 A5
    InstDummy,             // 01 A6
    InstDummy,             // 01 A7
    InstDummy,             // 01 A8
    InstDummy,             // 01 A9
    InstDummy,             // 01 AA
    InstDummy,             // 01 AB
    InstDummy,             // 01 AC
    InstDummy,             // 01 AD
    InstDummy,             // 01 AE
    InstDummy,             // 01 AF
    InstDummy,             // 01 B0
    InstDummy,             // 01 B1
    InstDummy,             // 01 B2
    InstDummy,             // 01 B3
    InstDummy,             // 01 B4
    InstDummy,             // 01 B5
    InstDummy,             // 01 B6
    InstDummy,             // 01 B7
    InstDummy,             // 01 B8
    InstDummy,             // 01 B9
    InstDummy,             // 01 BA
    InstDummy,             // 01 BB
    InstDummy,             // 01 BC
    InstDummy,             // 01 BD
    InstDummy,             // 01 BE
    InstDummy,             // 01 BF
    InstDummy,             // 01 C0
    InstDummy,             // 01 C1
    InstDummy,             // 01 C2
    InstDummy,             // 01 C3
    InstDummy,             // 01 C4
    InstDummy,             // 01 C5
    InstDummy,             // 01 C6
    InstDummy,             // 01 C7
    InstDummy,             // 01 C8
    InstDummy,             // 01 C9
    InstDummy,             // 01 CA
    InstDummy,             // 01 CB
    InstDummy,             // 01 CC
    InstDummy,             // 01 CD
    InstDummy,             // 01 CE
    InstDummy,             // 01 CF
    InstDummy,             // 01 D0
    InstDummy,             // 01 D1
    InstDummy,             // 01 D2
    InstDummy,             // 01 D3
    InstDummy,             // 01 D4
    InstDummy,             // 01 D5
    InstDummy,             // 01 D6
    InstDummy,             // 01 D7
    InstDummy,             // 01 D8
    InstDummy,             // 01 D9
    InstDummy,             // 01 DA
    InstDummy,             // 01 DB
    InstDummy,             // 01 DC
    InstDummy,             // 01 DD
    InstDummy,             // 01 DE
    InstDummy,             // 01 DF
    InstDummy,             // 01 E0
    InstDummy,             // 01 E1
    InstDummy,             // 01 E2
    InstDummy,             // 01 E3
    InstDummy,             // 01 E4
    InstDummy,             // 01 E5
    InstDummy,             // 01 E6
    InstDummy,             // 01 E7
    InstDummy,             // 01 E8
    InstDummy,             // 01 E9
    InstDummy,             // 01 EA
    InstDummy,             // 01 EB
    InstDummy,             // 01 EC
    InstDummy,             // 01 ED
    InstDummy,             // 01 EE
    InstDummy,             // 01 EF
    InstDummy,             // 01 F0
    InstDummy,             // 01 F1
    InstDummy,             // 01 F2
    InstDummy,             // 01 F3
    InstDummy,             // 01 F4
    InstDummy,             // 01 F5
    InstDummy,             // 01 F6
    InstDummy,             // 01 F7
    InstDummy,             // 01 F8
    InstDummy,             // 01 F9
    InstDummy,             // 01 FA
    InstDummy,             // 01 FB
    InstDummy,             // 01 FC
    InstDummy,             // 01 FD
    InstDummy,             // 01 FE
    InstDummy              // 01 FF
};

InstructionProc inline constexpr OpcodeTableUser1_CC[256] = {
    InstMSinit,            // 10 00
    InstBGload,            // 10 01
    InstBGswap,            // 10 02
    InstBGsetColor,        // 10 03
    InstBGsetLink,         // 10 04
    InstCHAload,           // 10 05
    InstCHAswap,           // 10 06
    InstBGcopy,            // 10 07
    InstCHAcopy,           // 10 08
    InstSaveSlot,          // 10 09
    InstSystemMain,        // 10 0A
    InstCharaLayerLoad,    // 10 0B
    InstGameInfoInit,      // 10 0C
    InstCHAmove,           // 10 0D
    InstBGloadEx,          // 10 0E
    InstDummy,             // 10 0F
    InstBGrelease,         // 10 10
    InstCHArelease,        // 10 11
    InstClearFlagChk,      // 10 12
    InstOption,            // 10 13
    InstSystemDataReset,   // 10 14
    InstDebugData,         // 10 15
    InstGetCharaPause,     // 10 16
    InstBGfadeExpInit,     // 10 17
    InstDummy,             // 10 18
    InstDummy,             // 10 19
    InstHelp,              // 10 1A
    InstDummy,             // 10 1B
    InstAchievementMenu,   // 10 1C
    InstSoundMenu,         // 10 1D
    InstAllClear,          // 10 1E
    InstAlbum,             // 10 1F
    InstMovieMode,         // 10 20
    InstClistInit,         // 10 21
    InstAutoSave,          // 10 22
    InstSaveMenu,          // 10 23
    InstLoadData,          // 10 24
    InstDummy,             // 10 25
    InstDummy,             // 10 26
    InstSetDic,            // 10 27
    InstSetPlayMode,       // 10 28
    InstSetEVflag,         // 10 29
    InstSetCutin,          // 10 2A
    InstDummy,             // 10 2B
    InstDummy,             // 10 2C
    InstAchChkTitle,       // 10 2D
    InstSetSceneViewFlag,  // 10 2E
    InstChkClearFlag,      // 10 2F
    InstBGeffectWave,      // 10 30
    InstGeotag,            // 10 31
    InstNameID,            // 10 32
    InstTips,              // 10 33
    InstTitleMenuNew,      // 10 34
    InstDummy,             // 10 35
    InstBGeffect,          // 10 36
    InstMapSystem,         // 10 37
    InstMtrg,              // 10 38
    InstTwipo_Dash,        // 10 39
    InstYesNoTriggerCCLCC, // 10 3A
    InstDummy,             // 10 3B
    InstDummy,             // 10 3C
    InstDummy,             // 10 3D
    InstDummy,             // 10 3E
    InstDummy,             // 10 3F
    InstScreenChange,      // 10 40
    InstExitGame,          // 10 41
    InstDummy,             // 10 42
    InstDummy,             // 10 43
    InstDummy,             // 10 44
    InstDummy,             // 10 45
    InstDummy,             // 10 46
    InstDummy,             // 10 47
    InstDummy,             // 10 48
    InstDummy,             // 10 49
    InstDummy,             // 10 4A
    InstDummy,             // 10 4B
    InstDummy,             // 10 4C
    InstDummy,             // 10 4D
    InstDummy,             // 10 4E
    InstDummy,             // 10 4F
    InstDummy,             // 10 50
    InstDummy,             // 10 51
    InstDummy,             // 10 52
    InstDummy,             // 10 53
    InstDummy,             // 10 54
    InstDummy,             // 10 55
    InstDummy,             // 10 56
    InstDummy,             // 10 57
    InstDummy,             // 10 58
    InstDummy,             // 10 59
    InstDummy,             // 10 5A
    InstDummy,             // 10 5B
    InstDummy,             // 10 5C
    InstDummy,             // 10 5D
    InstDummy,             // 10 5E
    InstDummy,             // 10 5F
    InstDummy,             // 10 60
    InstDummy,             // 10 61
    InstDummy,             // 10 62
    InstDummy,             // 10 63
    InstDummy,             // 10 64
    InstDummy,             // 10 65
    InstDummy,             // 10 66
    InstDummy,             // 10 67
    InstDummy,             // 10 68
    InstDummy,             // 10 69
    InstDummy,             // 10 6A
    InstDummy,             // 10 6B
    InstDummy,             // 10 6C
    InstDummy,             // 10 6D
    InstDummy,             // 10 6E
    InstDummy,             // 10 6F
    InstDummy,             // 10 70
    InstDummy,             // 10 71
    InstDummy,             // 10 72
    InstDummy,             // 10 73
    InstDummy,             // 10 74
    InstDummy,             // 10 75
    InstDummy,             // 10 76
    InstDummy,             // 10 77
    InstDummy,             // 10 78
    InstDummy,             // 10 79
    InstDummy,             // 10 7A
    InstDummy,             // 10 7B
    InstDummy,             // 10 7C
    InstDummy,             // 10 7D
    InstDummy,             // 10 7E
    InstDummy,             // 10 7F
    InstDummy,             // 10 80
    InstDummy,             // 10 81
    InstDummy,             // 10 82
    InstDummy,             // 10 83
    InstDummy,             // 10 84
    InstDummy,             // 10 85
    InstDummy,             // 10 86
    InstDummy,             // 10 87
    InstDummy,             // 10 88
    InstDummy,             // 10 89
    InstDummy,             // 10 8A
    InstDummy,             // 10 8B
    InstDummy,             // 10 8C
    InstDummy,             // 10 8D
    InstDummy,             // 10 8E
    InstDummy,             // 10 8F
    InstDummy,             // 10 90
    InstDummy,             // 10 91
    InstDummy,             // 10 92
    InstDummy,             // 10 93
    InstDummy,             // 10 94
    InstDummy,             // 10 95
    InstDummy,             // 10 96
    InstDummy,             // 10 97
    InstDummy,             // 10 98
    InstDummy,             // 10 99
    InstDummy,             // 10 9A
    InstDummy,             // 10 9B
    InstDummy,             // 10 9C
    InstDummy,             // 10 9D
    InstDummy,             // 10 9E
    InstDummy,             // 10 9F
    InstDummy,             // 10 A0
    InstDummy,             // 10 A1
    InstDummy,             // 10 A2
    InstDummy,             // 10 A3
    InstDummy,             // 10 A4
    InstDummy,             // 10 A5
    InstDummy,             // 10 A6
    InstDummy,             // 10 A7
    InstDummy,             // 10 A8
    InstDummy,             // 10 A9
    InstDummy,             // 10 AA
    InstDummy,             // 10 AB
    InstDummy,             // 10 AC
    InstDummy,             // 10 AD
    InstDummy,             // 10 AE
    InstDummy,             // 10 AF
    InstDummy,             // 10 B0
    InstDummy,             // 10 B1
    InstDummy,             // 10 B2
    InstDummy,             // 10 B3
    InstDummy,             // 10 B4
    InstDummy,             // 10 B5
    InstDummy,             // 10 B6
    InstDummy,             // 10 B7
    InstDummy,             // 10 B8
    InstDummy,             // 10 B9
    InstDummy,             // 10 BA
    InstDummy,             // 10 BB
    InstDummy,             // 10 BC
    InstDummy,             // 10 BD
    InstDummy,             // 10 BE
    InstDummy,             // 10 BF
    InstDummy,             // 10 C0
    InstDummy,             // 10 C1
    InstDummy,             // 10 C2
    InstDummy,             // 10 C3
    InstDummy,             // 10 C4
    InstDummy,             // 10 C5
    InstDummy,             // 10 C6
    InstDummy,             // 10 C7
    InstDummy,             // 10 C8
    InstDummy,             // 10 C9
    InstDummy,             // 10 CA
    InstDummy,             // 10 CB
    InstDummy,             // 10 CC
    InstDummy,             // 10 CD
    InstDummy,             // 10 CE
    InstDummy,             // 10 CF
    InstDummy,             // 10 D0
    InstDummy,             // 10 D1
    InstDummy,             // 10 D2
    InstDummy,             // 10 D3
    InstDummy,             // 10 D4
    InstDummy,             // 10 D5
    InstDummy,             // 10 D6
    InstDummy,             // 10 D7
    InstDummy,             // 10 D8
    InstDummy,             // 10 D9
    InstDummy,             // 10 DA
    InstDummy,             // 10 DB
    InstDummy,             // 10 DC
    InstDummy,             // 10 DD
    InstDummy,             // 10 DE
    InstDummy,             // 10 DF
    InstDummy,             // 10 E0
    InstDummy,             // 10 E1
    InstDummy,             // 10 E2
    InstDummy,             // 10 E3
    InstDummy,             // 10 E4
    InstDummy,             // 10 E5
    InstDummy,             // 10 E6
    InstDummy,             // 10 E7
    InstDummy,             // 10 E8
    InstDummy,             // 10 E9
    InstDummy,             // 10 EA
    InstDummy,             // 10 EB
    InstDummy,             // 10 EC
    InstDummy,             // 10 ED
    InstDummy,             // 10 EE
    InstDummy,             // 10 EF
    InstDummy,             // 10 F0
    InstDummy,             // 10 F1
    InstDummy,             // 10 F2
    InstDummy,             // 10 F3
    InstDummy,             // 10 F4
    InstDummy,             // 10 F5
    InstDummy,             // 10 F6
    InstDummy,             // 10 F7
    InstDummy,             // 10 F8
    InstDummy,             // 10 F9
    InstDummy,             // 10 FA
    InstDummy,             // 10 FB
    InstDummy,             // 10 FC
    InstDummy,             // 10 FD
    InstDummy,             // 10 FE
    InstDummy              // 10 FF
};

}

}

// clang-format on