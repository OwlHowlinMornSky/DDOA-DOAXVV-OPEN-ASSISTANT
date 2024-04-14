namespace WinFormsGUI {
	partial class FormSort {
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
			userControlList1 = new UserControlList();
			listBox1 = new ListBox();
			SuspendLayout();
			// 
			// userControlList1
			// 
			userControlList1.Location = new Point(84, 72);
			userControlList1.Name = "userControlList1";
			userControlList1.Size = new Size(150, 150);
			userControlList1.TabIndex = 0;
			// 
			// listBox1
			// 
			listBox1.FormattingEnabled = true;
			listBox1.ItemHeight = 17;
			listBox1.Items.AddRange(new object[] { "1", "2", "34", "54", "6", "7" });
			listBox1.Location = new Point(459, 163);
			listBox1.Name = "listBox1";
			listBox1.Size = new Size(120, 89);
			listBox1.TabIndex = 1;
			// 
			// FormSort
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(800, 450);
			Controls.Add(listBox1);
			Controls.Add(userControlList1);
			Name = "FormSort";
			Text = "FormSort";
			ResumeLayout(false);
		}

		#endregion

		private UserControlList userControlList1;
		private ListBox listBox1;
	}
}