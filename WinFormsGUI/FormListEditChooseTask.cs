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
	public partial class FormListEditChooseTask : Form {

		public uint choosedTask = (uint)TaskEnumWrap.None;

		public FormListEditChooseTask(string TipText) {
			InitializeComponent();
			Text += TipText;
		}

		private void FormListEditChooseTask_Load(object sender, EventArgs e) {
			for (uint i = (uint)TaskEnumWrap.None + 1, n = (uint)TaskEnumWrap.COUNT;
				i < n;
				i++) {
				listBox1.Items.Add(Strings.Main.ResourceManager.GetString("Task" + i.ToString("000")));
			}
		}

		private void listBox1_SelectedIndexChanged(object sender, EventArgs e) {
			if (listBox1.SelectedIndex == -1)
				choosedTask = (uint)TaskEnumWrap.None;
			else
				choosedTask = (uint)listBox1.SelectedIndex - (uint)TaskEnumWrap.None + 1;
		}

		private void button1_Click(object sender, EventArgs e) {
			DialogResult = DialogResult.OK;
		}

		private void button2_Click(object sender, EventArgs e) {
			choosedTask = (uint)TaskEnumWrap.None;
			DialogResult = DialogResult.Cancel;
		}
	}
}
