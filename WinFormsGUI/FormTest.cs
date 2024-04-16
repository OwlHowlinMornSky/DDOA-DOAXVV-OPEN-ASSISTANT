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
namespace WinFormsGUI {
	public partial class FormTest : Form {
		public FormTest() {
			InitializeComponent();

			SetStyle(ControlStyles.AllPaintingInWmPaint, true);
		}

		protected override void WndProc(ref Message m) {
			if (m.Msg == 0x0014) // 禁掉清除背景消息
				return;
			base.WndProc(ref m);
		}


		private void FormTest_Load(object sender, EventArgs e) {
			int n = 3;
			userControlLogger1.Log("RRSSF", Color.DarkRed);
			for (int i = 0; i < n; ++i) {

				userControlLogger1.Log("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试\r\nyi\r\n二ereererererererer" + i);

			}


		}

		private void FormTest_FormClosed(object sender, FormClosedEventArgs e) {
			userControlList1.OnClose();

			Settings.GUI.Default.Save();
		}

		private void button1_Click(object sender, EventArgs e) {
			SuspendLayout();
			userControlLogger1.Log("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试\r\nyi\r\n二ereererererererer");
			ResumeLayout();
		}
	}
}
