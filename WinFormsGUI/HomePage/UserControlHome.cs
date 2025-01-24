/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2025  Tyler Parret True
* 
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
* 
*        http://www.apache.org/licenses/LICENSE-2.0
* 
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
* 
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/

namespace WinFormsGUI {
	/// <summary>
	/// 主页。
	/// </summary>
	public partial class UserControlHome : UserControl {

		/// <summary>
		/// 当前主按钮状态
		/// </summary>
		internal enum BtmMainStatus {
			Start = 0,
			Stop
		};
		private BtmMainStatus m_btnMainStatus = BtmMainStatus.Start;

		/// <summary>
		/// 发托盘消息的回调，应由根窗口设置。
		/// </summary>
		public Action<string, string, ToolTipIcon> MyPopNotification = (x, y, z) => {};
		/// <summary>
		/// 当前展示的设置对应任务的id。
		/// </summary>
		private uint m_setIdNow = (uint)Helper.Step.Type.None;

		public UserControlHome() {
			InitializeComponent();
			// 设置左侧列表“设置小按钮”选择项改变的回调。
			userControlList.SetSelectedChangedTo += ChangeSettingCallback;
			// 注册以在工作时锁定控件。
			GlobalSetter.Regist.OnStartLock += OnTaskStartLock;
			GlobalSetter.Regist.OnLockWork += OnWorkLockAndUnlock;
			if (GlobalSetter.Regist.LockedStepDaily)
				OnWorkLockAndUnlock(true);
			GlobalSetter.Regist.Pause += OnTaskPause;
			GlobalSetter.Regist.Log += Log;
		}

		~UserControlHome() {
			GlobalSetter.Regist.Pause -= OnTaskPause;
			GlobalSetter.Regist.OnLockWork -= OnWorkLockAndUnlock;
			userControlList.SetSelectedChangedTo -= ChangeSettingCallback;
		}

		private void Log(Helper.GUICallbacks.LogInfo info) {
			Log(info.title,
					info.type switch {
						Helper.GUICallbacks.LogInfo.Type.Info => Color.DimGray,
						Helper.GUICallbacks.LogInfo.Type.Notice => userControlLogger.SystemColor,
						Helper.GUICallbacks.LogInfo.Type.Warn => Color.Blue,
						Helper.GUICallbacks.LogInfo.Type.Error => Color.Red,
						_ => Color.DimGray
					}
				);
			if (info.description != null)
				Log(info.description);
			if (info.notify)
				MyPopNotification(
					info.title,
					info.description ?? "   ",
					info.type switch {
						Helper.GUICallbacks.LogInfo.Type.Info => ToolTipIcon.Info,
						Helper.GUICallbacks.LogInfo.Type.Notice => ToolTipIcon.Info,
						Helper.GUICallbacks.LogInfo.Type.Warn => ToolTipIcon.Warning,
						Helper.GUICallbacks.LogInfo.Type.Error => ToolTipIcon.Error,
						_ => ToolTipIcon.None
					}
					);
		}

		internal void OnTaskStartLock() {
			button_Main.Enabled = false;
		}

		/// <summary>
		/// 监听工作状态改变锁定控件的事件
		/// </summary>
		private void OnWorkLockAndUnlock(bool locked) {
			void f(bool isLock) {
				if (isLock) {
					button_Main.Enabled = true;
					m_btnMainStatus = BtmMainStatus.Stop;
					button_Main.Text = Strings.Main.Btn_Main_Stop;
				}
				else {
					button_Main.Enabled = true;
					m_btnMainStatus = BtmMainStatus.Start;
					button_Main.Text = Strings.Main.Btn_Main_Start;
				}
			}
			if (InvokeRequired) {
				var r = BeginInvoke(f, locked);
				EndInvoke(r);
			}
			else {
				f(locked);
			}
		}

		private void OnTaskPause() {
			var r = BeginInvoke(() => {
				button_Resume.Visible = true;
				SetListMiddle();
			});
			EndInvoke(r);
		}

		/// <summary>
		/// 修改展示的设置页
		/// </summary>
		/// <param name="id">内部任务id</param>
		private void ChangeSetting(uint id) {
			if (m_setIdNow == id) // 页面不改变
				return;
			panel_Settings.Controls.Clear(); // 清除当前页面
			Control ctrl;
			switch ((Helper.Step.Type)id) { // 选择页面
			default:
			case Helper.Step.Type.None:
				id = (uint)Helper.Step.Type.None;
				ctrl = new UserControlSetForDefault();
				break;
			//case TaskEnumWrap.StartUp:
			//	break;
			case Helper.Step.Type.Daily:
				ctrl = new UserControlSetForDaily();
				break;
			case Helper.Step.Type.Challenge:
				ctrl = new UserControlSetForChallenge();
				break;
			}
			ctrl.Dock = DockStyle.Fill;
			// 添加页面
			panel_Settings.Controls.Add(ctrl);
			m_setIdNow = id;
		}

		/// <summary>
		/// 改变设置页面的回调
		/// </summary>
		/// <param name="data">项数据</param>
		private void ChangeSettingCallback(uint data) {
			if (InvokeRequired) {
				var r = BeginInvoke(new Action(() => {
					ChangeSetting(data);
				}));
				EndInvoke(r);
			}
			else {
				ChangeSetting(data);
			}
		}

		/// <summary>
		/// 【转接】清空日志
		/// </summary>
		public void ClearLog() => userControlLogger.Clear();
		/// <summary>
		/// 【转接】添加日志
		/// </summary>
		/// <param name="message">文本内容</param>
		/// <param name="color">颜色</param>
		public void Log(string message, Color color) => userControlLogger.Log(message, color);
		/// <summary>
		/// 【转接】添加日志（默认颜色）
		/// </summary>
		/// <param name="message">文本内容</param>
		public void Log(string message) => userControlLogger.Log(message);

		/// <summary>
		/// 控件加载时
		/// </summary>
		private void UserControlHome_Load(object sender, EventArgs e) {
			button_Resume.Visible = false;
			SetListMiddle();
			button_Main.Text = Strings.Main.Btn_Main_Start;
		}

		/// <summary>
		/// 【需手动调用】尝试关闭时
		/// </summary>
		public void OnClosing() {
			userControlList.OnClosing();
		}

		/// <summary>
		/// 把左侧第一列内容在其panel中居中
		/// </summary>
		private void SetListMiddle() {
			userControlList.Left = (panel_leftCtrl.Width - userControlList.Width) / 2;
			if (button_Resume.Visible) {
				button_Main.Left = panel_leftCtrl.Width / 2 - button_Main.Width - 2;
				button_Resume.Left = panel_leftCtrl.Width / 2 + 2;
			}
			else {
				button_Main.Left = (panel_leftCtrl.Width - button_Main.Width) / 2;
			}
		}

		/// <summary>
		/// 左侧panel大小改变后
		/// </summary>
		private void Panel_LeftCtrl_SizeChanged(object sender, EventArgs e) {
			SetListMiddle(); // 重新居中
		}

		/// <summary>
		/// 点击主按钮
		/// </summary>
		private void Button_Main_Click(object sender, EventArgs e) {
			button_Main.Enabled = false;
			switch (m_btnMainStatus) {
			case BtmMainStatus.Start: {
				ClearLog(); // 清空进度提示。

				var list = userControlList.GetEnabledList();
				if (list.Count == 0) {
					Log(Strings.Main.TaskListNotSelected);
					break;
				}

				if (Settings.Core.Default.PlayMatchType == 2) {
					if (Settings.Core.Default.PlayLevel == 0 || Settings.Core.Default.PlayLevelR == 0) {
						Log(Strings.Main.ChallengeActivityLevelNotSelected);
						break;
					}
				}

				GlobalSetter.ApplySettings();

				try {
					Helper.Worker.StartWork(list.Select(num => (Helper.Step.Type)num));
					GlobalSetter.Regist.OnStartLock();
				}
				catch (Exception) {
					Log(Strings.Main.TaskWorkStartFailed); // 提示。
				}
				break;
			}
			case BtmMainStatus.Stop: { // 要求停止
				Helper.Worker.TryCancelWork();
				break;
			}
			}
		}

		private void Button_Resume_Click(object sender, EventArgs e) {
			GlobalSetter.ApplySettings();
			Helper.Worker.Resume();
			button_Resume.Visible = false;
			SetListMiddle();
		}

	}
}
