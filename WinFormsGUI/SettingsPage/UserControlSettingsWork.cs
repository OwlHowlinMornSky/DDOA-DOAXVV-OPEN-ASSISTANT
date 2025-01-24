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

using System.Net.Sockets;

namespace WinFormsGUI.SettingsPage {
	public partial class UserControlSettingsWork : UserControl {
		public UserControlSettingsWork() {
			InitializeComponent();
			// 注册以在工作时锁定控件。
			GlobalSetter.Regist.OnLockWork += OnWorkLockAndUnlock;
			if (GlobalSetter.Regist.LockedStepDaily)
				OnWorkLockAndUnlock(true);
		}

		~UserControlSettingsWork() {
			GlobalSetter.Regist.OnLockWork -= OnWorkLockAndUnlock;
		}

		/// <summary>
		/// 监听工作状态改变锁定控件的事件
		/// </summary>
		private void OnWorkLockAndUnlock(bool locked) {
			void f(bool isLock) {
				Enabled = !isLock;
			}
			if (InvokeRequired) {
				var r = BeginInvoke(f, locked);
				EndInvoke(r);
			}
			else {
				f(locked);
			}
		}

		private void UserControlSettingsWork_Load(object sender, EventArgs e) {
#if DEBUG
			chkBox_SetShow.Visible = true;
#endif
			chkBox_SetShow.Checked = Settings.Core.Default.ShowCapture;
			if (Settings.Core.Default.KeepAwake) {
				chkBox_SetAwake.Checked = true;
				chkBox_SetScreenOn.Enabled = true;
				chkBox_SetScreenOn.Checked = Settings.Core.Default.KeepScreenOn;
			}
			else {
				chkBox_SetAwake.Checked = false;
				chkBox_SetScreenOn.Enabled = false;
				chkBox_SetScreenOn.Checked = false;
			}
		}

		private void ChkBox_SetAwake_CheckedChanged(object sender, EventArgs e) {
			if (chkBox_SetAwake.Checked) {
				chkBox_SetAwake.Checked = true;
				chkBox_SetScreenOn.Enabled = true;
				Settings.Core.Default.KeepAwake = true;
			}
			else {
				chkBox_SetAwake.Checked = false;
				chkBox_SetScreenOn.Enabled = false;
				chkBox_SetScreenOn.Checked = false;
				Settings.Core.Default.KeepAwake = false;
			}
		}

		private void ChkBox_SetScreenOn_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.KeepScreenOn = chkBox_SetScreenOn.Checked;
		}

		private void ChkBox_SetShow_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.ShowCapture = chkBox_SetShow.Checked;
		}
	}
}
