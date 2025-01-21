using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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

		internal static Pattern? CreatePattern(string name) {
			if (!m_infos.TryGetValue(name, out Pattern.Info info))
				return null;
			return new Pattern(Path.Combine(m_folder, name), info);
		}
	}
}
