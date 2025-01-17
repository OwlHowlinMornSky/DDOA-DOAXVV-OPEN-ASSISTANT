
namespace Helper {
	static public class Settings {

		public struct Global() {
			public bool KeepAwake    = true;  // 阻止睡眠。
			public bool KeepScreenOn = false; // 同时保持显示。
		};
		public static Global global;

		public struct WndHandler() {
			public bool UseSendInput       = false; // 选择控制鼠标。
			public bool UseHook            = false; // 是否使用挂钩。

			public bool Debug_ShowCapture  = false; // [调试] 是否显示截取到的帧。
			public bool Debug_DebugHandler = false; // [调试] 是否以DDOA调试器为目标。
		};
		public static WndHandler wndHandler;

		public struct Challenge() {
			public int  PlayMatch             = 0;     // 0: Previous; 1: New; 2: Activity
			public int  SelectedActivityLevel = 0;     // -EDCBAS...
			public int  SelectedActivityMatch = 0;     // 0123456...
			public bool EnterAddition         = false; // 进入奖励挑战赛。默认不进入奖励挑战赛。
			public bool CheckAddition         = false; // 是否检查奖励挑战赛。默认不检查奖励挑战赛。
			public bool AutoUseCamFP          = false; // 是否自动使用每日拍摄的补充FP。默认不使用拍摄补充FP。
			public bool AskForManual          = false; // 是否在开始时请求手动导航。默认不暂停。
			public bool AutoUseDrink          = false; // 是否自动使用饮料补充FP。默认不使用饮料。
		}
		public static Challenge challenge;

		public struct Daily() {
			public bool DoCheck = true; // 是否每日签到。默认进行每日签到。
			public bool DoShot  = true; // 是否每日拍摄。默认进行每日拍摄。
		}
		public static Daily daily;
	}
}
