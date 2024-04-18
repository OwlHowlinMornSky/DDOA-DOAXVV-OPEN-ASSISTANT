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
using static System.Runtime.InteropServices.JavaScript.JSType;

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
		private readonly int vScrollBarWidth = 20;

		private bool m_autoResizeItem = false;
		public int itemCntLimit = 128;

		public UserControlLogger() {
			InitializeComponent();

			var test = new VScrollBar();
			vScrollBarWidth = test.Width;
		}

		public void SetAutoResizeItem(bool value) {
			m_autoResizeItem = value;
			listBox1.BeginUpdate();
			listBox1.SuspendLayout();
			SuspendLayout();
			var ti = listBox1.TopIndex;
			listBox1.DrawMode = DrawMode.OwnerDrawFixed;
			listBox1.DrawMode = DrawMode.OwnerDrawVariable;
			listBox1.TopIndex = ti;
			ResumeLayout();
			listBox1.ResumeLayout();
			listBox1.EndUpdate();
		}

		public bool GetAutoResizeItem() {
			return m_autoResizeItem;
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

		public void Clear() {
			listBox1.Items.Clear();
		}

		public void LogProcessStatusChange(bool isBegin) {
			if (isBegin) {
				listBox1.BeginUpdate();
				listBox1.SuspendLayout();
				SuspendLayout();
			}
			else {
				ResumeLayout();
				listBox1.ResumeLayout();
				listBox1.EndUpdate();
			}
		}

		private void LogAdd(string message, Color color) {
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
			while (listBox1.Items.Count > itemCntLimit)
				listBox1.Items.RemoveAt(0);
			if (scroll)
				listBox1.TopIndex = listBox1.Items.Count - 1;
			return;
		}

		public void Log(string message, Color color) {
			if (InvokeRequired) {
				var r = BeginInvoke(new Action(() => {
					LogAdd(message, color);
				}));
				EndInvoke(r);
			}
			else {
				LogAdd(message, color);
			}
		}

		public void Log(string message) {
			Log(message, Color.DimGray);
		}

		private void ListBox1_DrawItem(object sender, DrawItemEventArgs e) {
			var listBox = sender as ListBox;
			if (e.Index < 0)
				return;
			var item = (LogItem)listBox.Items[e.Index];

			e.Graphics.FillRectangle(new SolidBrush(Control.DefaultBackColor), e.Bounds);
			var sz0 = e.Graphics.MeasureString(item.time, e.Font);

			var b = e.Bounds;
			e.Graphics.DrawString(item.time, e.Font, new SolidBrush(item.hideTime ? Control.DefaultBackColor : m_sysClr), b);
			b.Offset(sz0.ToSize().Width, 0);
			if (m_autoResizeItem)
				b.Width = listBox.Width - sz0.ToSize().Width - vScrollBarWidth - 1;
			else
				b.Width -= sz0.ToSize().Width;
			e.Graphics.DrawString(item.str, e.Font, new SolidBrush(item.color), b);
		}

		private void ListBox1_MeasureItem(object sender, MeasureItemEventArgs e) {
			var listBox = sender as ListBox;
			var item = (LogItem)listBox.Items[e.Index];

			var sz0 = e.Graphics.MeasureString(item.time, listBox.Font);
			SizeF sz1;
			if (m_autoResizeItem)
				sz1 = e.Graphics.MeasureString(item.str, listBox.Font, listBox.Width - sz0.ToSize().Width - vScrollBarWidth - 1);
			else
				sz1 = e.Graphics.MeasureString(item.str, listBox.Font);

			var W = (int)(sz0.Width + sz1.Width);
			var H = (int)Math.Max(sz0.Height, sz1.Height);

			listBox.HorizontalExtent = W;
			e.ItemHeight = H + 6;
			e.ItemWidth = W;
		}

		private void UserControlLogger_SizeChanged(object sender, EventArgs e) {
			if (!m_autoResizeItem)
				return;
			listBox1.BeginUpdate();
			listBox1.SuspendLayout();
			SuspendLayout();
			var ti = listBox1.TopIndex;
			listBox1.DrawMode = DrawMode.OwnerDrawFixed;
			listBox1.DrawMode = DrawMode.OwnerDrawVariable;
			listBox1.TopIndex = ti;
			listBox1.ResumeLayout();
			ResumeLayout();
			listBox1.EndUpdate();
		}
	}
}
