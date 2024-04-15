namespace WinFormsGUI {
	partial class FormListEdit {
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormListEdit));
			listBox1 = new ListBox();
			button_add = new Button();
			button_Insert = new Button();
			button_modify = new Button();
			button_remove = new Button();
			button_moveup = new Button();
			button_movedown = new Button();
			button_cancel = new Button();
			button_ok = new Button();
			button_clearAll = new Button();
			SuspendLayout();
			// 
			// listBox1
			// 
			listBox1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			listBox1.FormattingEnabled = true;
			listBox1.IntegralHeight = false;
			listBox1.ItemHeight = 17;
			listBox1.Location = new Point(12, 12);
			listBox1.Name = "listBox1";
			listBox1.Size = new Size(239, 357);
			listBox1.TabIndex = 2;
			listBox1.SelectedIndexChanged += listBox1_SelectedIndexChanged;
			// 
			// button_add
			// 
			button_add.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			button_add.Location = new Point(257, 12);
			button_add.Name = "button_add";
			button_add.Size = new Size(75, 23);
			button_add.TabIndex = 3;
			button_add.Text = "新增";
			button_add.UseVisualStyleBackColor = true;
			button_add.Click += button_add_Click;
			// 
			// button_Insert
			// 
			button_Insert.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			button_Insert.Enabled = false;
			button_Insert.Location = new Point(257, 41);
			button_Insert.Name = "button_Insert";
			button_Insert.Size = new Size(75, 23);
			button_Insert.TabIndex = 4;
			button_Insert.Text = "插入";
			button_Insert.UseVisualStyleBackColor = true;
			button_Insert.Click += button_Insert_Click;
			// 
			// button_modify
			// 
			button_modify.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			button_modify.Enabled = false;
			button_modify.Location = new Point(257, 70);
			button_modify.Name = "button_modify";
			button_modify.Size = new Size(75, 23);
			button_modify.TabIndex = 5;
			button_modify.Text = "编辑";
			button_modify.UseVisualStyleBackColor = true;
			button_modify.Click += button_modify_Click;
			// 
			// button_remove
			// 
			button_remove.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			button_remove.Enabled = false;
			button_remove.Location = new Point(257, 99);
			button_remove.Name = "button_remove";
			button_remove.Size = new Size(75, 23);
			button_remove.TabIndex = 6;
			button_remove.Text = "移除";
			button_remove.UseVisualStyleBackColor = true;
			button_remove.Click += button_remove_Click;
			// 
			// button_moveup
			// 
			button_moveup.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			button_moveup.Enabled = false;
			button_moveup.Location = new Point(257, 162);
			button_moveup.Name = "button_moveup";
			button_moveup.Size = new Size(75, 23);
			button_moveup.TabIndex = 7;
			button_moveup.Text = "上移";
			button_moveup.UseVisualStyleBackColor = true;
			button_moveup.Click += button_moveup_Click;
			// 
			// button_movedown
			// 
			button_movedown.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			button_movedown.Enabled = false;
			button_movedown.Location = new Point(257, 191);
			button_movedown.Name = "button_movedown";
			button_movedown.Size = new Size(75, 23);
			button_movedown.TabIndex = 8;
			button_movedown.Text = "下移";
			button_movedown.UseVisualStyleBackColor = true;
			button_movedown.Click += button_movedown_Click;
			// 
			// button_cancel
			// 
			button_cancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			button_cancel.DialogResult = DialogResult.Cancel;
			button_cancel.Location = new Point(257, 346);
			button_cancel.Name = "button_cancel";
			button_cancel.Size = new Size(75, 23);
			button_cancel.TabIndex = 0;
			button_cancel.Text = "取消";
			button_cancel.UseVisualStyleBackColor = true;
			// 
			// button_ok
			// 
			button_ok.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			button_ok.DialogResult = DialogResult.OK;
			button_ok.Location = new Point(257, 317);
			button_ok.Name = "button_ok";
			button_ok.Size = new Size(75, 23);
			button_ok.TabIndex = 1;
			button_ok.Text = "确定";
			button_ok.UseVisualStyleBackColor = true;
			// 
			// button_clearAll
			// 
			button_clearAll.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			button_clearAll.Location = new Point(257, 251);
			button_clearAll.Name = "button_clearAll";
			button_clearAll.Size = new Size(75, 23);
			button_clearAll.TabIndex = 9;
			button_clearAll.Text = "清空";
			button_clearAll.Click += button_clearAll_Click;
			// 
			// FormListEdit
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(344, 404);
			ControlBox = false;
			Controls.Add(button_clearAll);
			Controls.Add(button_ok);
			Controls.Add(button_cancel);
			Controls.Add(button_movedown);
			Controls.Add(button_moveup);
			Controls.Add(button_remove);
			Controls.Add(button_modify);
			Controls.Add(button_Insert);
			Controls.Add(button_add);
			Controls.Add(listBox1);
			Icon = (Icon)resources.GetObject("$this.Icon");
			MaximizeBox = false;
			MinimizeBox = false;
			MinimumSize = new Size(360, 420);
			Name = "FormListEdit";
			ShowInTaskbar = false;
			StartPosition = FormStartPosition.CenterParent;
			Text = "编辑任务列表";
			ResumeLayout(false);
		}

		#endregion

		private ListBox listBox1;
		private Button button_add;
		private Button button_Insert;
		private Button button_modify;
		private Button button_remove;
		private Button button_moveup;
		private Button button_movedown;
		private Button button_cancel;
		private Button button_ok;
		private Button button_clearAll;
	}
}