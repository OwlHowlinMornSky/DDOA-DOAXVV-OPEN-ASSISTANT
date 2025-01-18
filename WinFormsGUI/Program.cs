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
using Wrapper;

namespace WinFormsGUI {
	internal static class Program {

		/// <summary>
		/// Helper套壳的实例。
		/// </summary>
		internal readonly static HelperWrapper helper = new();

		/// <summary>
		///  The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() {
			// To customize application configuration such as set high DPI settings or default font,
			// see https://aka.ms/applicationconfiguration.
			ApplicationConfiguration.Initialize();
			if (!SetupHelper())
				return;
			GlobalSetter.InitSettings();
			Application.Run(new FormNew());
			GlobalSetter.SaveSettings();
			helper.Drop();
		}

		static bool SetupHelper() {
			int initCode = helper.Setup();
			if (initCode != 0) {
				switch (initCode) {
				case 1:
					MessageBox.Show(
						Strings.Main.ProgramCoreInitializationFailed_CoreLogOpenFailed,
						"DDOA: " + Strings.Main.ProgramCoreInitializationFailed,
						MessageBoxButtons.OK,
						MessageBoxIcon.Error
					);
					break;
				case 2:
					MessageBox.Show(
						Strings.Main.ProgramCoreInitializationFailed_LoadTemplateListFailed,
						"DDOA: " + Strings.Main.ProgramCoreInitializationFailed,
						MessageBoxButtons.OK,
						MessageBoxIcon.Error
					);
					break;
				default:
					MessageBox.Show(
						Strings.Main.ProgramCoreInitializationFailed_UnknownReason,
						"DDOA: " + Strings.Main.ProgramCoreInitializationFailed,
						MessageBoxButtons.OK,
						MessageBoxIcon.Error
					);
					break;
				}
				return false;
			}


			Helper.Global.PatternManager.LoadFromFile(@"assets\tempLists.ini");

			return true;
		}
	}
}
