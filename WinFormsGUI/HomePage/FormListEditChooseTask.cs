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
using System.Windows.Forms;
using Wrapper;

namespace WinFormsGUI {
	/// <summary>
	/// 编辑“主页左侧任务列表”窗口的附属窗口，用于选择目标任务项。
	/// </summary>
	public partial class FormListEditChooseTask : Form {

		/// <summary>
		/// 选择的任务项id
		/// </summary>
		public uint choosedTask = (uint)TaskEnumWrap.None;

		/// <summary>
		/// 构造函数
		/// </summary>
		/// <param name="TipText">窗口标题的提示文本</param>
		public FormListEditChooseTask(string TipText) {
			InitializeComponent();
			Text += TipText;
		}

		/// <summary>
		/// 窗口加载时。
		/// </summary>
		private void FormListEditChooseTask_Load(object sender, EventArgs e) {
			listBox1.BeginUpdate();
			// 将所有可用的任务项列出
			for (uint i = (uint)TaskEnumWrap.None + 1, n = (uint)TaskEnumWrap.COUNT;
				i < n; i++) {
				listBox1.Items.Add(Strings.Main.ResourceManager.GetString("Task" + i.ToString("000")));
			}
#if DEBUG
			listBox1.Items.Add(Strings.Main.ResourceManager.GetString("Task" + ((uint)TaskEnumWrap.TEST_TASK).ToString("000")));
#endif
			listBox1.EndUpdate();
		}

		/// <summary>
		/// ListBox改变选择时。
		/// </summary>
		private void ListBox1_SelectedIndexChanged(object sender, EventArgs e) {
			// 修改选择项的记录。
			if (listBox1.SelectedIndex == -1)
				choosedTask = (uint)TaskEnumWrap.None;
			else
				choosedTask = (uint)listBox1.SelectedIndex - (uint)TaskEnumWrap.None + 1;
#if DEBUG
			if (choosedTask >= (uint)TaskEnumWrap.COUNT) {
				choosedTask = (uint)TaskEnumWrap.TEST_TASK;
			}
#endif
		}

		/// <summary>
		/// 点击“确定”按钮。
		/// </summary>
		private void Button1_Click(object sender, EventArgs e) {
			DialogResult = DialogResult.OK;
		}

		/// <summary>
		/// 点击“取消”按钮。
		/// </summary>
		private void button2_Click(object sender, EventArgs e) {
			choosedTask = (uint)TaskEnumWrap.None; // 清除选择。
			DialogResult = DialogResult.Cancel;
		}

		private void listBox1_DoubleClick(object sender, EventArgs e) {
			DialogResult = DialogResult.OK;
		}
	}
}
