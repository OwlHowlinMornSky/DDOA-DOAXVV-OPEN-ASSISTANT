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
	/// 测试用窗口
	/// </summary>
	public partial class FormNew : Form {

		public FormNew() {
			InitializeComponent();
			SetStyle(ControlStyles.OptimizedDoubleBuffer, true);

			userControlHome1.MyPopNotification += PopNotification;
			GlobalSetter.OnSettedWndCloseBtnDisabled += OnWndCloseBtnDisabled;
		}

		~FormNew() {
			GlobalSetter.OnSettedWndCloseBtnDisabled -= OnWndCloseBtnDisabled;
			userControlHome1.MyPopNotification -= PopNotification;
		}

		private void OnWndCloseBtnDisabled(bool disabled) {
			Wrapper.SystemThings.SetCloseEnabled(Handle, !disabled);
		}

		private void FormNew_Load(object sender, EventArgs e) {
			OnWndCloseBtnDisabled(Settings.GUI.Default.DisableClose);
			if (Settings.GUI.Default.WndLastPosition.Y > -1)
				Location = Settings.GUI.Default.WndLastPosition;
			notifyIcon_Main.Text = Text;
		}

		/// <summary>
		/// 窗口试图关闭
		/// </summary>
		private void FormNew_FormClosing(object sender, FormClosingEventArgs e) {
			if (Program.helper.IsRunning()) {
				if (e.CloseReason != CloseReason.WindowsShutDown) {
					// 询问是否关闭
					var res = MessageBox.Show(
						Strings.Main.QueryClose,
						Text,
						MessageBoxButtons.OKCancel,
						MessageBoxIcon.Question
					);
					if (res == DialogResult.Cancel) {
						e.Cancel = true;
						return;
					}
				}
				Program.helper.AskForStop();
				while (Program.helper.IsRunning()) {
					Thread.Sleep(100);
				}
			}
			userControlHome1.OnClosing();
			Show();
			WindowState = FormWindowState.Normal;
			Activate();
			Settings.GUI.Default.WndLastPosition = Location;
		}

		/// <summary>
		/// 窗口已关闭。
		/// </summary>
		private void FormNew_FormClosed(object sender, FormClosedEventArgs e) {
		}

		private void NotifyIcon_Main_MouseClick(object sender, MouseEventArgs e) {
			switch (e.Button) {
			case MouseButtons.Left:
				Show();
				WindowState = FormWindowState.Normal;
				Activate();
				if (Settings.GUI.Default.DisableClose)
					Wrapper.SystemThings.SetCloseEnabled(Handle, false);
				break;
			case MouseButtons.Right:
				notifyIcon_Main.ContextMenuStrip?.Show();
				break;
			}
		}

		/// <summary>
		/// 发送托盘消息。
		/// </summary>
		/// <param name="title">消息标题</param>
		/// <param name="text">消息内容</param>
		/// <param name="icon">消息图标</param>
		private void PopNotification(string title, string text, ToolTipIcon icon) {
			if (Settings.GUI.Default.UseNotify)
				notifyIcon_Main.ShowBalloonTip(
					Settings.Param.Default.NotifyTime,
					title,
					text,
					icon
				);
		}

		/// <summary>
		/// 点击托盘图标右键菜单的“退出”项。
		/// </summary>
		private void ToolStripMenuItem_Exit_Click(object sender, EventArgs e) {
			Close();
		}

		private const int WM_SYSCOMMAND = 0x112;
		private const int SC_CLOSE = 0xF060;
		private const int SC_MINIMIZE = 0xF020;
		private const int SC_MAXIMIZE = 0xF030;
		private const int SC_RESTORE = 61728;
		protected override void WndProc(ref Message m) {
			base.WndProc(ref m);
			if (m.Msg == WM_SYSCOMMAND) {
				switch (m.WParam.ToInt32() & 0xFFF0) {
				case SC_MINIMIZE:
					if (Settings.GUI.Default.HideToTray)
						Hide();
					break;
				case SC_RESTORE:
					if (Settings.GUI.Default.DisableClose)
						Wrapper.SystemThings.SetCloseEnabled(Handle, false);
					break;
				}
			}
		}
	}
}
