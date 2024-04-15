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
			flowLayoutPanel1 = new FlowLayoutPanel();
			label1 = new Label();
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
			// flowLayoutPanel1
			// 
			flowLayoutPanel1.BackColor = Color.IndianRed;
			flowLayoutPanel1.Location = new Point(301, 74);
			flowLayoutPanel1.Name = "flowLayoutPanel1";
			flowLayoutPanel1.Size = new Size(273, 144);
			flowLayoutPanel1.TabIndex = 1;
			// 
			// label1
			// 
			label1.AutoSize = true;
			label1.Location = new Point(377, 237);
			label1.Name = "label1";
			label1.Size = new Size(43, 17);
			label1.TabIndex = 2;
			label1.Text = "label1";
			// 
			// FormTest
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(800, 450);
			Controls.Add(label1);
			Controls.Add(flowLayoutPanel1);
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
		private FlowLayoutPanel flowLayoutPanel1;
		private Label label1;
	}
}