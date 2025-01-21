/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2025  Tyler Parret True
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

namespace Helper {
	public static class GUICallbacks {
		public struct LogInfo(LogInfo.Type type, string title, string? desc = null) {
			public enum Type {
				Info,
				Warn,
				Error
			}
			public Type type = type;
			public string title = title;
			public string? description = desc;
		}
		public static Action<LogInfo> Log { set; internal get; } = (x) => { };

		public static Action<bool> LockTask { set; internal get; } = (x) => { };
		public static Action<bool, Step.Type> LockSettings { set; internal get; } = (x, y) => { };
		public static Action Pause { set; internal get; } = () => { };
	}
}
