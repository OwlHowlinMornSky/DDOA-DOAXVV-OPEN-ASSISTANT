/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2024  Tyler Parret True
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
using Wrapper;

namespace WinFormsGUI {
	/// <summary>
	/// 放入控件确认身份的数据
	/// </summary>
	public struct ListItemUserData {
		/// <summary>
		/// 对应的内部任务id
		/// </summary>
		public uint coreTaskEnum;
		/// <summary>
		/// 在列表中的次序
		/// </summary>
		public int rank;
	}

	/// <summary>
	/// 主页左侧任务列表控件
	/// </summary>
	public partial class UserControlList : UserControl {

		/// <summary>
		/// 保存的任务完整列表
		/// </summary>
		private List<uint> m_listTasks = [];
		/// <summary>
		/// 选择的设置小按钮改变id时的callback
		/// </summary>
		public Action<uint> SetSelectedChangedTo = x => {};

		public UserControlList() {
			InitializeComponent();
			// 注册以在工作时锁定控件。
			Program.GuiLock += OnWorkLockAndUnlock;
		}

		/// <summary>
		/// 监听工作状态改变锁定控件的事件
		/// </summary>
		private void OnWorkLockAndUnlock(object sender, bool isLock) {
			if (isLock) {
				button_all.Enabled = false;
				button_clear.Enabled = false;
				for (int i = 0, n = flowLayoutPanel1.Controls.Count; i < n; i += 2) {
					flowLayoutPanel1.Controls[i].Enabled = false;
				}
			}
			else {
				for (int i = 0, n = flowLayoutPanel1.Controls.Count; i < n; i += 2) {
					flowLayoutPanel1.Controls[i].Enabled = true;
				}
				button_clear.Enabled = true;
				button_all.Enabled = true;
			}
		}

		/// <summary>
		/// 获取勾选了的任务列表
		/// </summary>
		/// <returns>任务列表</returns>
		public List<uint> GetEnabledList() {
			List<uint> list = [];
			for (int i = 0, n = flowLayoutPanel1.Controls.Count; i < n; i += 2) {
				if (flowLayoutPanel1.Controls[i] is CheckBox checkBox && checkBox.Checked) {
					list.Add(((ListItemUserData)checkBox.DataContext).coreTaskEnum);
				}
			}
			return list;
		}

		private void SetList(List<uint> list) {
			SuspendLayout();
			flowLayoutPanel1.SuspendLayout();
			m_listTasks = list;
			flowLayoutPanel1.Controls.Clear();
			int cnt = 0;
			foreach (var i in list) {
				ListItemUserData data = new() {
					coreTaskEnum = i,
					rank = cnt
				};
				cnt++;

				var checkBox = new CheckBox() {
					DataContext = data,
					Width = 135,
					Text = Strings.Main.ResourceManager.GetString("Task" + i.ToString("000")),
				};
				checkBox.CheckedChanged += OnListCheckBoxChanged;
				checkBox.MouseEnter += OnListCheckBoxEnter;
				checkBox.MouseLeave += OnListCheckBoxLeave;
				flowLayoutPanel1.Controls.Add(checkBox);

				var radioBtn = new RadioButton() {
					DataContext = data,
					Width = 24,
					Height = 24,
					Image = Resources.Img.set0,
					Appearance = Appearance.Button,
				};
				radioBtn.CheckedChanged += OnListRadioBtnChanged;
				radioBtn.MouseEnter += OnListRadioBtnEnter;
				radioBtn.MouseLeave += OnListRadioBtnLeave;
				radioBtn.KeyDown += OnListRadioBtnKeyDown;
				flowLayoutPanel1.Controls.Add(radioBtn);
				flowLayoutPanel1.SetFlowBreak(radioBtn, true);
			}
			flowLayoutPanel1.ResumeLayout();
			ResumeLayout();
		}

		private void OnListCheckBoxChanged(object sender, EventArgs e) {
			var checkBox = sender as CheckBox;
			var data = (ListItemUserData)checkBox.DataContext;
			int rank = data.rank;
		}

		private void OnListRadioBtnChanged(object sender, EventArgs e) {
			var radioBtn = sender as RadioButton;
			var data = (ListItemUserData)radioBtn.DataContext;
			int rank = data.rank;
			if (radioBtn.Checked) {
				SetSelectedChangedTo(data.coreTaskEnum);
			}
		}

		private void OnListCheckBoxEnter(object sender, EventArgs e) {
			var ctrl = sender as Control;
			ctrl.BackColor = Color.LightBlue;
		}

		private void OnListCheckBoxLeave(object sender, EventArgs e) {
			var ctrl = sender as Control;
			ctrl.BackColor = CheckBox.DefaultBackColor;
		}

		private void OnListRadioBtnEnter(object sender, EventArgs e) {
			var ctrl = sender as Control;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = Color.LightBlue;
		}

		private void OnListRadioBtnLeave(object sender, EventArgs e) {
			var ctrl = sender as Control;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = CheckBox.DefaultBackColor;
		}

		private void OnClickChooseAll(object sender, EventArgs e) {
			foreach (var ctrl in flowLayoutPanel1.Controls) {
				if (ctrl is CheckBox checkBox) {
					checkBox.Checked = true;
				}
			}
		}

		private void OnClickClearList(object sender, EventArgs e) {
			foreach (var ctrl in flowLayoutPanel1.Controls) {
				if (ctrl is CheckBox checkBox) {
					checkBox.Checked = false;
				}
			}
		}

		/// <summary>
		/// 触发“修改”。
		/// </summary>
		private void OnClickEditList(object sender, EventArgs args) {
			var dialog = new FormListEdit {
				ListTasks = m_listTasks
			}; // 打开修改窗口
			var res = dialog.ShowDialog();
			if (res == DialogResult.OK) { // 确认即修改。
				SetList(dialog.ListTasks);
				OnClickChooseAll(null, null);
			}
		}

		static public List<uint> GetTaskListFromSettingString() {
			string str = Settings.GUI.Default.ListItems;
			var strs = str.Split(',');
			List<uint> tasks = [];
			foreach (var s in strs) {
				if (s.Length == 0)
					continue;
				var n = uint.Parse(s);
				if (n > (uint)TaskEnumWrap.None)
					tasks.Add(n);
			}
			return tasks;
		}

		private void UserControlList_Load(object sender, EventArgs e) {
			SetList(GetTaskListFromSettingString());

			var str = Settings.GUI.Default.ListItemCheckList;
			var strs = str.Split(',');
			foreach (var s in strs) {
				if (s.Length == 0)
					continue;
				var n = int.Parse(s);
				((CheckBox)flowLayoutPanel1.Controls[n * 2]).Checked = true;
			}

			if (Settings.GUI.Default.ListLastSelectedSettings >= 0) {
				(flowLayoutPanel1.Controls[
					Settings.GUI.Default.ListLastSelectedSettings * 2 + 1
				] as RadioButton).Checked = true;
			}
		}

		/// <summary>
		/// 需要手动调用
		/// </summary>
		public void OnClosing() {
			string str = "";
			foreach (var s in m_listTasks) {
				if (s > (uint)TaskEnumWrap.None) {
					str += s;
					str += ',';
				}
			}
			Settings.GUI.Default.ListItems = str;

			str = "";
			int selectedSet = -1;
			foreach (var ctrl in flowLayoutPanel1.Controls) {
				if (ctrl.GetType() == typeof(CheckBox)) {
					var checkBox = ctrl as CheckBox;
					if (checkBox.Checked) {
						str += ((ListItemUserData)checkBox.DataContext).rank;
						str += ',';
					}
				}
				else {
					var radioBtn = ctrl as RadioButton;
					if (radioBtn.Checked) {
						selectedSet = ((ListItemUserData)radioBtn.DataContext).rank;
					}
				}
			}
			Settings.GUI.Default.ListItemCheckList = str;
			Settings.GUI.Default.ListLastSelectedSettings = selectedSet;
		}

		private void OnListRadioBtnKeyDown(object sender, KeyEventArgs e) {
			if (e.KeyCode != Keys.Escape)
				return;
			for (int i = 1, n = flowLayoutPanel1.Controls.Count; i < n; i += 2) {
				var radioBtn = flowLayoutPanel1.Controls[i] as RadioButton;
				radioBtn.Checked = false;
			}
			SetSelectedChangedTo((uint)TaskEnumWrap.None);
		}
	}
}
