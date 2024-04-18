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
	/// 编辑“主页左侧任务列表”的窗口。
	/// </summary>
	public partial class FormListEdit : Form {

		/// <summary>
		/// 内部保存的完整列表。
		/// </summary>
		private List<uint> m_listTasks = [];

		/// <summary>
		/// 对外展示的完整列表。
		/// </summary>
		public List<uint> ListTasks {
			get {
				return m_listTasks;
			}
			set {
				m_listTasks = value;
				OnListSeted(); // 刷新控件
			}
		}

		public FormListEdit() {
			InitializeComponent();
		}

		/// <summary>
		/// 完整列表更新后刷新控件。
		/// </summary>
		private void OnListSeted() {
			listBox1.BeginUpdate();
			listBox1.ClearSelected();
			listBox1.Items.Clear();
			foreach (var task in m_listTasks) {
				listBox1.Items.Add(
					Strings.Main.ResourceManager.GetString("Task" + task.ToString("000"))
				);
			}
			listBox1.EndUpdate();
		}

		/// <summary>
		/// 点击“添加”按钮。
		/// </summary>
		private void Button_add_Click(object sender, EventArgs e) {
			if (m_listTasks.Count >= (int)TaskEnumWrap.TaskMaxNum) {
				MessageBox.Show($"The limit of task length is {(int)TaskEnumWrap.TaskMaxNum}.");
				return;
			}
			var choose = new FormListEditChooseTask(((Button)sender).Text);
			var res = choose.ShowDialog();
			var choice = choose.choosedTask;
			if (res == DialogResult.Cancel || choice == (uint)TaskEnumWrap.None)
				return;
			m_listTasks.Add(choice);
			listBox1.Items.Add(
				Strings.Main.ResourceManager.GetString("Task" + choice.ToString("000"))
			);
		}

		/// <summary>
		/// 点击“插入”按钮。
		/// </summary>
		private void Button_Insert_Click(object sender, EventArgs e) {
			if (m_listTasks.Count >= (int)TaskEnumWrap.TaskMaxNum) {
				MessageBox.Show($"The limit of task length is {(int)TaskEnumWrap.TaskMaxNum}.");
				return;
			}
			var choose = new FormListEditChooseTask(((Button)sender).Text);
			var res = choose.ShowDialog();
			var choice = choose.choosedTask;
			if (res == DialogResult.Cancel || choice == (uint)TaskEnumWrap.None)
				return;
			var index = listBox1.SelectedIndex;
			m_listTasks.Insert(index, choice);
			listBox1.Items.Insert(
				index,
				Strings.Main.ResourceManager.GetString("Task" + choice.ToString("000"))
			);
			listBox1.SelectedIndex--; // 选择刚插入的项
		}

		/// <summary>
		/// 点击“修改”按钮。
		/// </summary>
		private void Button_modify_Click(object sender, EventArgs e) {
			var choose = new FormListEditChooseTask(((Button)sender).Text);
			var res = choose.ShowDialog();
			var choice = choose.choosedTask;
			if (res == DialogResult.Cancel || choice == (uint)TaskEnumWrap.None)
				return;
			var index = listBox1.SelectedIndex;
			m_listTasks[index] = choice;
			listBox1.Items[index] =
				Strings.Main.ResourceManager.GetString("Task" + choice.ToString("000"));
		}

		/// <summary>
		/// 点击“移除”按钮。
		/// </summary>
		private void Button_remove_Click(object sender, EventArgs e) {
			// 保存旧位置
			var index = listBox1.SelectedIndex;

			listBox1.Items.RemoveAt(index);
			m_listTasks.RemoveAt(index);
			
			// 还原旧选中位置
			if(index >= listBox1.Items.Count)
				index = listBox1.Items.Count - 1;
			listBox1.SelectedIndex = index;
		}

		/// <summary>
		/// 点击“清空”按钮。
		/// </summary>
		private void Button_clearAll_Click(object sender, EventArgs e) {
			listBox1.ClearSelected();
			listBox1.Items.Clear();
			m_listTasks.Clear();
		}

		/// <summary>
		/// 点击“上移”按钮。
		/// </summary>
		private void Button_moveup_Click(object sender, EventArgs e) {
			var index = listBox1.SelectedIndex;
			if (index == 0)
				return;
			(m_listTasks[index - 1], m_listTasks[index]) =
				(m_listTasks[index], m_listTasks[index - 1]);
			(listBox1.Items[index - 1], listBox1.Items[index]) =
				(listBox1.Items[index], listBox1.Items[index - 1]);
			listBox1.SelectedIndex--;
		}

		/// <summary>
		/// 点击“下移”按钮。
		/// </summary>
		private void Button_movedown_Click(object sender, EventArgs e) {
			var index = listBox1.SelectedIndex;
			if (index == m_listTasks.Count - 1)
				return;
			(m_listTasks[index], m_listTasks[index + 1]) =
				(m_listTasks[index + 1], m_listTasks[index]);
			(listBox1.Items[index], listBox1.Items[index + 1]) =
				(listBox1.Items[index + 1], listBox1.Items[index]);
			listBox1.SelectedIndex++;
		}

		/// <summary>
		/// ListBox选中项改变。
		/// </summary>
		private void ListBox1_SelectedIndexChanged(object sender, EventArgs e) {
			if (listBox1.SelectedIndex != -1) { // 选中了一项时启用针对单项修改的控件。
				button_Insert.Enabled = true;
				button_modify.Enabled = true;
				button_remove.Enabled = true;
				button_moveup.Enabled = true;
				button_movedown.Enabled = true;
			}
			else { // 取消选择时禁用之。
				button_Insert.Enabled = false;
				button_modify.Enabled = false;
				button_remove.Enabled = false;
				button_moveup.Enabled = false;
				button_movedown.Enabled = false;
			}
		}

		/// <summary>
		/// 点击“重置”按钮。
		/// </summary>
		private void Button_reset_Click(object sender, EventArgs e) {
			Settings.GUI.Default.Reset(); // 重置所有设置。
			ListTasks = UserControlList.GetTaskListFromSettingString();
			Settings.GUI.Default.Reload(); // 重新读取保存的设置。
		}
	}
}
