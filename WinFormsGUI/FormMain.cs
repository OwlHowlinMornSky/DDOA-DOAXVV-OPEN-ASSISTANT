using System.Windows.Forms;
using Wrapper;

namespace WinFormsGUI {
	public partial class FormMain : Form {

		#region ==========Members==========

		private HelperWrapper m_helper = new();
		private bool m_btnMainIsStart = true;

		#endregion

		#region ==========Common===========

		public FormMain() {
			InitializeComponent();
		}

		public void Log(string msg) {
			bool scroll = listBox_Main.TopIndex == listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
			listBox_Main.Items.Add(msg);
			if (scroll)
				listBox_Main.TopIndex = listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
		}

		public void Log() {
			bool scroll = listBox_Main.TopIndex == listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
			listBox_Main.Items.Add("");
			if (scroll)
				listBox_Main.TopIndex = listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
		}

		#endregion

		#region ==========Events===========

		#region ---------MainForm----------

		public void FormMain_Load(object sender, EventArgs e) {
			button_Tab0_Main.Text = Strings.str.Main_Btn_Start;

			radioButton_Tab0_Box0_1.Checked = Settings.main.Default.Game_ForNew;
			radioButton_Tab0_Box1_1.Checked = Settings.main.Default.Ctrl_ForMouse;
			checkBox_Tab1_showCV.Checked = Settings.main.Default.ShowCV;
		}

		private void FormMain_FormClosing(object sender, FormClosingEventArgs e) {
			m_helper.askForStop();

			Settings.main.Default.Game_ForNew = radioButton_Tab0_Box0_1.Checked;
			Settings.main.Default.Ctrl_ForMouse = radioButton_Tab0_Box1_1.Checked;
			Settings.main.Default.ShowCV = checkBox_Tab1_showCV.Checked;

			Settings.main.Default.Save();

			while (m_helper.isRunning()) {
				Thread.Sleep(30);
			}
		}

		private void FormMain_FormClosed(object sender, FormClosedEventArgs e) {
		}

		#endregion

		#region -----------Tab0------------

		private void button_Tab0_Main_Click(object sender, EventArgs e) {
			groupBox_Tab0_Box0.Enabled = false;
			groupBox_Tab0_Box1.Enabled = false;
			button_Tab0_Main.Enabled = false;

			if (m_btnMainIsStart) {
				listBox_Main.Items.Clear();

				if (!m_helper.start()) {
					Log(Strings.str.Main_Log_CanNotStartWork);
					return;
				}
				timer1.Enabled = true;
			}
			else {
				m_helper.askForStop();
			}
		}

		private void radioButton_Tab0_Box0_0_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box0_0.Checked)
				m_helper.set(HelprSet.Cha_New, 0);
		}

		private void radioButton_Tab0_Box0_1_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box0_1.Checked)
				m_helper.set(HelprSet.Cha_New, 1);
		}

		private void radioButton_Tab0_Box1_0_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box1_0.Checked)
				m_helper.set(HelprSet.Ctrl_MouseInput, 0);
		}

		private void radioButton_Tab0_Box1_1_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box1_1.Checked)
				m_helper.set(HelprSet.Ctrl_MouseInput, 1);
		}
		#endregion

		#region -----------Tab1------------

		private void checkBox_Tab1_showCV_CheckedChanged(object sender, EventArgs e) {
			if (checkBox_Tab1_showCV.Checked)
				m_helper.set(HelprSet.ShowCV, 1);
			else
				m_helper.set(HelprSet.ShowCV, 0);
		}

		#endregion

		private void timer1_Tick(object sender, EventArgs e) {
			ReturnMessage m = m_helper.msgPop();
			switch (m) {
			case ReturnMessage.Stopped:
				Log(Strings.str.Main_Log_WorkStopped);
				groupBox_Tab0_Box0.Enabled = true;
				groupBox_Tab0_Box1.Enabled = true;
				timer1.Enabled = false;
				break;
			case ReturnMessage.BtnToStop:
				button_Tab0_Main.Text = Strings.str.Main_Btn_Stop;
				button_Tab0_Main.Enabled = true;
				m_btnMainIsStart = false;
				break;
			case ReturnMessage.BtnToStart:
				button_Tab0_Main.Text = Strings.str.Main_Btn_Start;
				button_Tab0_Main.Enabled = true;
				m_btnMainIsStart = true;
				break;
			case ReturnMessage.Log_ErrorIsRunning:
				Log(Strings.str.Main_Log_WorkAlreadyRunning);
				break;
			case ReturnMessage.Log_Stopping:
				Log(Strings.str.Main_Log_WorkStopping);
				break;
			case ReturnMessage.Log_ErrorNotFindWnd:
				Log(Strings.str.Main_Log_CanNotFindWnd);
				break;
			case ReturnMessage.Log_ErrorCannotCapture:
				Log(Strings.str.Main_Log_CanNotCapture);
				break;
			case ReturnMessage.Log_ErrorInWork:
				Log();
				Log(Strings.str.Main_Log_ExceptionInWork);
				MessageBox.Show(
					this,
					Strings.str.Main_Log_ExceptionInWork,
					Strings.str.Main_Log_WorkError,
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
					);
				break;
			case ReturnMessage.Log_ErrorInTask:
				Log();
				Log(Strings.str.Main_Log_WorkError);
				break;

			case ReturnMessage.Log_Challenge_Start:
				Log(Strings.str.Main_Log_Challenge_Start);
				break;
			case ReturnMessage.Log_Challenge_BeginNum: // 挑战赛开始（下跟次数！）
				Log(string.Format(Strings.str.Main_Log_Challenge_BeginNum, m_helper.codePop()));
				break;
			case ReturnMessage.Log_Challenge_EnterLast:
				Log(Strings.str.Main_Log_Challenge_EnterLast);
				break;
			case ReturnMessage.Log_Challenge_EnterNew:
				Log(Strings.str.Main_Log_Challenge_EnterNew);
				break;
			case ReturnMessage.Log_Challenge_Play:
				Log(Strings.str.Main_Log_Challenge_Play);
				break;
			case ReturnMessage.Log_Challenge_WaitForEnd:
				Log(Strings.str.Main_Log_Challenge_WaitForEnd);
				break;
			case ReturnMessage.Log_Challenge_End:
				Log(Strings.str.Main_Log_Challenge_End);
				break;
			case ReturnMessage.Log_Challenge_Quiting:
				Log(Strings.str.Main_Log_Challenge_Quiting);
				break;
			case ReturnMessage.Log_Challenge_Over:
				Log(Strings.str.Log_Challenge_Over);
				break;
			case ReturnMessage.Log_Challenge_Exit:
				Log(Strings.str.Log_Challenge_Exit);
				break;

			case ReturnMessage.Log_Task_Stop:
				Log(Strings.str.Log_Task_Stop);
				break;
			case ReturnMessage.Log_Task_Exception:
				Log(Strings.str.Log_Task_Exception);
				MessageBox.Show(
					this,
					Strings.str.Log_Task_Exception,
					Strings.str.Main_Log_WorkError,
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
					);
				break;

			case ReturnMessage.Log_Task_Challenge_NoNew:
				Log(Strings.str.Log_Task_Challenge_NoNew);
				break;
			case ReturnMessage.Log_Task_Challenge_NoLast:
				Log(Strings.str.Log_Task_Challenge_NoLast);
				break;
			case ReturnMessage.Log_Task_Challenge_NoEnter:
				Log(Strings.str.Log_Task_Challenge_NoEnter);
				break;
			case ReturnMessage.Log_Task_Challenge_LowFP:
				Log(Strings.str.Log_Task_Challenge_LowFP);
				break;
			case ReturnMessage.Log_Task_Challenge_NoStart:
				Log(Strings.str.Log_Task_Challenge_NoStart);
				break;
			case ReturnMessage.Log_Task_Challenge_TimeOut:
				Log(Strings.str.Log_Task_Challenge_TimeOut);
				break;
			case ReturnMessage.Log_Task_Challenge_NoEnd:
				Log(Strings.str.Log_Task_Challenge_NoEnd);
				break;
			case ReturnMessage.Log_Task_Challenge_NoOver:
				Log(Strings.str.Log_Task_Challenge_NoOver);
				break;
			}
			return;
		}

		#endregion

	}
}
