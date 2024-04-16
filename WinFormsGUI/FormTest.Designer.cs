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
			components = new System.ComponentModel.Container();
			userControlList1 = new UserControlList();
			userControlLogger1 = new UserControlLogger();
			SuspendLayout();
			// 
			// userControlList1
			// 
			userControlList1.Dock = DockStyle.Fill;
			userControlList1.Location = new Point(0, 0);
			userControlList1.MaximumSize = new Size(180, 0);
			userControlList1.MinimumSize = new Size(180, 200);
			userControlList1.Name = "userControlList1";
			userControlList1.Size = new Size(180, 450);
			userControlList1.TabIndex = 0;
			// 
			// userControlLogger1
			// 
			userControlLogger1.AutoSize = true;
			userControlLogger1.Dock = DockStyle.Fill;
			userControlLogger1.Location = new Point(0, 0);
			userControlLogger1.Name = "userControlLogger1";
			userControlLogger1.Size = new Size(800, 450);
			userControlLogger1.TabIndex = 1;
			// 
			// FormTest
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(800, 450);
			Controls.Add(userControlLogger1);
			Controls.Add(userControlList1);
			Name = "FormTest";
			Text = "FormTest";
			FormClosed += FormTest_FormClosed;
			Load += FormTest_Load;
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private UserControlList userControlList1;
		private UserControlLogger userControlLogger1;
	}
}