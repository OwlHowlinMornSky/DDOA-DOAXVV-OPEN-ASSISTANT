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

	internal struct LogItem {
		public string time;
		public bool hideTime;
		public string str;
		public Color color;
		public override readonly string ToString() {
			return time + str;
		}
	}

	public partial class UserControlLogger : UserControl {

		[System.Runtime.InteropServices.DllImport("dwmapi.dll", PreserveSig = false)]
		public static extern void DwmGetColorizationColor(out int pcrColorization, out bool pfOpaqueBlend);
		public static Color GetSystemMainColor() {
			DwmGetColorizationColor(out int pcrColorization, out _);
			return Color.FromArgb(pcrColorization);
		}
		private readonly Color m_sysClr = GetSystemMainColor();
		private int vScrollBarWidth = 20;

		public UserControlLogger() {
			InitializeComponent();

			var test = new VScrollBar();
			vScrollBarWidth = test.Width;
		}

		protected override void WndProc(ref Message m) {
			if (m.Msg == 0x0014) // 禁掉清除背景消息
				return;
			base.WndProc(ref m);
		}

		private bool IsAtBottom() {
			int flag = listBox1.TopIndex;
			int sum = 0;
			Graphics g = Graphics.FromHwnd(listBox1.Handle);
			while (flag < listBox1.Items.Count) {
				MeasureItemEventArgs e = new(g, flag);
				ListBox1_MeasureItem(listBox1, e);
				sum += e.ItemHeight;
				if (sum > listBox1.Height)
					return false;
				flag++;
			}
			return true;
		}

		public void Log(string message, Color color) {
			SuspendLayout();
			bool scroll = IsAtBottom();
			var timeStr = DateTime.Now.ToString("MM/dd HH:mm:ss　");
			listBox1.Items.Add(
				new LogItem() {
					time = timeStr,
					hideTime = false,
					str = message,
					color = color
				}
			);
			if (scroll)
				listBox1.TopIndex = listBox1.Items.Count - 1;
			ResumeLayout();
		}

		public void Log(string message) {
			Log(message, Color.DimGray);
		}

		private void ListBox1_DrawItem(object sender, DrawItemEventArgs e) {
			var listBox = sender as ListBox;
			var item = (LogItem)listBox.Items[e.Index];

			e.Graphics.FillRectangle(new SolidBrush(Control.DefaultBackColor), e.Bounds);
			var sz0 = e.Graphics.MeasureString(item.time, e.Font);

			var b = e.Bounds;
			e.Graphics.DrawString(item.time, e.Font, new SolidBrush(item.hideTime ? Control.DefaultBackColor : m_sysClr), b);
			b.Offset(sz0.ToSize().Width, 0);
			b.Width = listBox.Width - sz0.ToSize().Width - vScrollBarWidth - 1;
			e.Graphics.DrawString(item.str, e.Font, new SolidBrush(item.color), b);
		}

		private void ListBox1_MeasureItem(object sender, MeasureItemEventArgs e) {
			var listBox = sender as ListBox;
			var item = (LogItem)listBox.Items[e.Index];

			var sz0 = e.Graphics.MeasureString(item.time, listBox.Font);
			var sz1 = e.Graphics.MeasureString(item.str, listBox.Font, listBox.Width - sz0.ToSize().Width - vScrollBarWidth - 1);

			var W = (int)(sz0.Width + sz1.Width);
			var H = (int)Math.Max(sz0.Height, sz1.Height);

			listBox.HorizontalExtent = W;
			e.ItemHeight = H + 6;
			e.ItemWidth = W;
		}

		private void UserControlLogger_SizeChanged(object sender, EventArgs e) {
			SuspendLayout();
			var ti = listBox1.TopIndex;
			listBox1.DrawMode = DrawMode.OwnerDrawFixed;
			listBox1.DrawMode = DrawMode.OwnerDrawVariable;
			ResumeLayout();
			listBox1.TopIndex = ti;
		}
	}
}
