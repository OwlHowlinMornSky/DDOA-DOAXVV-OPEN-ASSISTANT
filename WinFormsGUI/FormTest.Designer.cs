namespace WinFormsGUI {
	partial class FormTest {
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			tabControl1 = new TabControl();
			tabPage1 = new TabPage();
			userControlHome1 = new UserControlHome();
			tabPage2 = new TabPage();
			tabControl1.SuspendLayout();
			tabPage1.SuspendLayout();
			SuspendLayout();
			// 
			// tabControl1
			// 
			tabControl1.Controls.Add(tabPage1);
			tabControl1.Controls.Add(tabPage2);
			tabControl1.Dock = DockStyle.Fill;
			tabControl1.Location = new Point(0, 0);
			tabControl1.Name = "tabControl1";
			tabControl1.SelectedIndex = 0;
			tabControl1.Size = new Size(784, 521);
			tabControl1.TabIndex = 0;
			// 
			// tabPage1
			// 
			tabPage1.BackColor = SystemColors.Control;
			tabPage1.Controls.Add(userControlHome1);
			tabPage1.Location = new Point(4, 26);
			tabPage1.Name = "tabPage1";
			tabPage1.Padding = new Padding(3);
			tabPage1.Size = new Size(776, 491);
			tabPage1.TabIndex = 0;
			tabPage1.Text = "tabPage1";
			// 
			// userControlHome1
			// 
			userControlHome1.Dock = DockStyle.Fill;
			userControlHome1.Location = new Point(3, 3);
			userControlHome1.MinimumSize = new Size(580, 360);
			userControlHome1.Name = "userControlHome1";
			userControlHome1.Size = new Size(770, 485);
			userControlHome1.TabIndex = 0;
			// 
			// tabPage2
			// 
			tabPage2.Location = new Point(4, 26);
			tabPage2.Name = "tabPage2";
			tabPage2.Padding = new Padding(3);
			tabPage2.Size = new Size(616, 411);
			tabPage2.TabIndex = 1;
			tabPage2.Text = "tabPage2";
			tabPage2.UseVisualStyleBackColor = true;
			// 
			// FormTest
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(784, 521);
			Controls.Add(tabControl1);
			DoubleBuffered = true;
			MinimumSize = new Size(800, 560);
			Name = "FormTest";
			Text = "FormTest";
			FormClosed += FormTest_FormClosed;
			Load += FormTest_Load;
			tabControl1.ResumeLayout(false);
			tabPage1.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private TabControl tabControl1;
		private TabPage tabPage1;
		private TabPage tabPage2;
		private UserControlHome userControlHome1;
	}
}