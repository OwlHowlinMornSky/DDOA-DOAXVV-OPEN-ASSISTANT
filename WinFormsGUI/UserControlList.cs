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

	public struct ListItemUserData {
		public uint coreTaskEnum;
		public int rank;
	}

	public partial class UserControlList : UserControl {

		private List<uint> m_listTasks = [];

		public Action<ListItemUserData> SetSelectedChangedTo = x => {};

		public UserControlList() {
			InitializeComponent();
		}

		public List<uint> GetEnabledList() {
			List<uint> list = new List<uint>();
			for (int i = 0, n = flowLayoutPanel1.Controls.Count; i < n; i += 2) {
				var checkBox = flowLayoutPanel1.Controls[i] as CheckBox;
				if (checkBox != null && checkBox.Checked) {
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
					Image = Img.set0,
					Appearance = Appearance.Button,
				};
				radioBtn.CheckedChanged += OnListRadioBtnChanged;
				radioBtn.MouseEnter += OnListRadioBtnEnter;
				radioBtn.MouseLeave += OnListRadioBtnLeave;
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
			//MessageBox.Show($"CheckBox #{rank} Changed to {checkBox.Checked}.");
		}

		private void OnListRadioBtnChanged(object sender, EventArgs e) {
			var radioBtn = sender as RadioButton;
			var data = (ListItemUserData)radioBtn.DataContext;
			int rank = data.rank;
			if (radioBtn.Checked) {
				SetSelectedChangedTo(data);
			}
			//MessageBox.Show($"RadioBtn #{rank} Changed to {radioBtn.Checked}.");
		}

		private void OnListCheckBoxEnter(object sender, EventArgs e) {
			var ctrl = sender as Control;
			ctrl.BackColor = Color.LightBlue;
		}

		private void OnListCheckBoxLeave(object sender, EventArgs e) {
			var ctrl = sender as Control;
			ctrl.BackColor = Color.Transparent;
		}

		private void OnListRadioBtnEnter(object sender, EventArgs e) {
			var ctrl = sender as Control;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = Color.LightBlue;
		}

		private void OnListRadioBtnLeave(object sender, EventArgs e) {
			var ctrl = sender as Control;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = Color.Transparent;
		}

		private void OnClickChooseAll(object sender, EventArgs e) {
			foreach (var ctrl in flowLayoutPanel1.Controls) {
				if (ctrl.GetType() == typeof(CheckBox)) {
					var checkBox = (CheckBox)ctrl;
					checkBox.Checked = true;
				}
			}
		}

		private void OnClickClearList(object sender, EventArgs e) {
			foreach (var ctrl in flowLayoutPanel1.Controls) {
				if (ctrl.GetType() == typeof(CheckBox)) {
					var checkBox = (CheckBox)ctrl;
					checkBox.Checked = false;
				}
			}
		}
		
		/// <summary>
		/// 触发“修改”。
		/// </summary>
		private void OnClickEditList(object sender, EventArgs args) {
			var dialog = new FormListEdit(); // 打开修改窗口
			DialogResult res;
			do {
				dialog.ListTasks = m_listTasks;
				res = dialog.ShowDialog();
				if (res == DialogResult.Retry) { // 与修改窗口通信，需要“重置”时，重新加载列表。
					UserControlList_Load(null, null);
				}
			} while (res == DialogResult.Retry); // 与修改窗口通信，需要“重置”时，重新打开修改窗口。
			if (res == DialogResult.OK) { // 确认即修改。
				SetList(dialog.ListTasks);
				OnClickChooseAll(null, null);
			}
		}

		private void UserControlList_Load(object sender, EventArgs e) {
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
			SetList(tasks);

			str = Settings.GUI.Default.ListItemCheckList;
			strs = str.Split(',');
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
	}
}
