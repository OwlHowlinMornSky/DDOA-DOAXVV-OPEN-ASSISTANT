﻿//------------------------------------------------------------------------------
// <auto-generated>
//     此代码由工具生成。
//     运行时版本:4.0.30319.42000
//
//     对此文件的更改可能会导致不正确的行为，并且如果
//     重新生成代码，这些更改将会丢失。
// </auto-generated>
//------------------------------------------------------------------------------

namespace WinFormsGUI.Settings {
    
    
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "17.9.0.0")]
    internal sealed partial class Core : global::System.Configuration.ApplicationSettingsBase {
        
        private static Core defaultInstance = ((Core)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Core())));
        
        public static Core Default {
            get {
                return defaultInstance;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("False")]
        public bool Cha_PlayNew {
            get {
                return ((bool)(this["Cha_PlayNew"]));
            }
            set {
                this["Cha_PlayNew"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("False")]
        public bool CtrlSendInput {
            get {
                return ((bool)(this["CtrlSendInput"]));
            }
            set {
                this["CtrlSendInput"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("False")]
        public bool ShowCapture {
            get {
                return ((bool)(this["ShowCapture"]));
            }
            set {
                this["ShowCapture"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("True")]
        public bool KeepAwake {
            get {
                return ((bool)(this["KeepAwake"]));
            }
            set {
                this["KeepAwake"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("False")]
        public bool KeepScreenOn {
            get {
                return ((bool)(this["KeepScreenOn"]));
            }
            set {
                this["KeepScreenOn"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("0")]
        public int Cha_Award {
            get {
                return ((int)(this["Cha_Award"]));
            }
            set {
                this["Cha_Award"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("")]
        public string TaskList {
            get {
                return ((string)(this["TaskList"]));
            }
            set {
                this["TaskList"] = value;
            }
        }
    }
}
