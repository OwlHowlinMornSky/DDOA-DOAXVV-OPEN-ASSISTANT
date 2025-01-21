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
	public static class PatternManager {

		private static Dictionary<string, Pattern.Info> m_infos = [];
		private static string m_folder = "";

		public static void Clear() {
			m_infos.Clear();
			m_folder = "";
		}

		public static void LoadFromFile(string filepath) {
			Clear();

			m_folder = Path.GetDirectoryName(filepath) ?? throw new FileNotFoundException();

			FileStream fileStream = new(filepath, FileMode.Open, FileAccess.Read);
			StreamReader reader = new(fileStream);

			var line = reader.ReadLine();
			if (!int.TryParse(line, out int num))
				throw new TemplateListFormatException();

			for (int i = 0; i < num; ++i) {
				line = reader.ReadLine();
				if (line == null)
					break;
				var pars = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
				if (pars.Length < 8) {
					Clear();
					throw new TemplateListFormatException();
				}
				int offset = 0;

				string name = pars[offset++];
				Pattern.Info info = new();

				if (!int.TryParse(pars[offset++], out int tag)) {
					Clear();
					throw new TemplateListFormatException();
				}
				info.isFixed = (tag & 0x1) != 0;
				info.isMasked = (tag & 0x2) != 0;

				if (!int.TryParse(pars[offset++], out tag)) {
					Clear();
					throw new TemplateListFormatException();
				}
				info.threshold = tag / 65536.0f;


				if (!int.TryParse(pars[offset++], out int c0)) {
					Clear();
					throw new TemplateListFormatException();
				}
				if (!int.TryParse(pars[offset++], out int c1)) {
					Clear();
					throw new TemplateListFormatException();
				}
				if (!int.TryParse(pars[offset++], out int c2)) {
					Clear();
					throw new TemplateListFormatException();
				}
				if (!int.TryParse(pars[offset++], out int c3)) {
					Clear();
					throw new TemplateListFormatException();
				}
				info.rect = new(c0, c1, c2, c3);

				if (!int.TryParse(pars[offset++], out int nsp)) {
					Clear();
					throw new TemplateListFormatException();
				}
				for (int j = 0; j < nsp; j++) {
					if (!int.TryParse(pars[offset++], out int x)) {
						Clear();
						throw new TemplateListFormatException();
					}
					if (!int.TryParse(pars[offset++], out int y)) {
						Clear();
						throw new TemplateListFormatException();
					}
					info.points.Add(new(x, y));
				}

				m_infos.Add(name, info);
			}
		}

		internal static Pattern? TryCreatePattern(string name) {
			if (!m_infos.TryGetValue(name, out Pattern.Info info))
				return null;
			return new Pattern(Path.Combine(m_folder, name), info);
		}

		internal static Pattern CreatePattern(string name) {
			return TryCreatePattern(name) ?? throw new Exception();
		}
	}
}
