using System.Text.RegularExpressions;

namespace jour3
{
    internal class Program
    {
        static void Application(string ligne, ref long resultat)
        {
            var value = Regex.Matches(ligne, @"mul\(\d{1,3},\d{1,3}\)");
            for (int i = 0; i < value.Count; ++i)
            {
                string stringValue = value[i].Value;
                string value1 = stringValue.Substring(stringValue.IndexOf('(') + 1, stringValue.IndexOf(',') - stringValue.IndexOf('(') - 1);
                string value2 = stringValue.Substring(stringValue.IndexOf(',') + 1, stringValue.IndexOf(')') - stringValue.IndexOf(',') - 1);

                resultat += long.Parse(value1) * long.Parse(value2);
            }
        }

        static List<string> ReadFile()
        {
            List<string> lignes = new();
            StreamReader streamReader = new("input.txt");
            while (!streamReader.EndOfStream)
            {
                lignes.Add(streamReader.ReadLine()!);
            }
            return lignes;
        }

        static void Main(string[] args)
        {
            var donnees = ReadFile(); //new List<string>() { "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))" };
            long resultat = 0L;

            foreach (var ligne in donnees)
            {
                Application(ligne, ref resultat);
            }

            Console.WriteLine(resultat);

            string exemple = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
            exemple = Regex.Replace(exemple, @"don\'t\(\).*?do\(\)", "");
            Console.WriteLine(exemple);

            long resultat2 = 0L;

            string grosseLigne = "";//string.Join("", donnees);
            bool lireDebut = true;
            for (int i = 0; i < donnees.Count; ++i)
            {
                if (!lireDebut)
                {
                    donnees[i] = donnees[i].Remove(0, donnees[i].IndexOf("do()"));
                }

                MatchCollection collectionDo = Regex.Matches(donnees[i], "do\\(\\)");
                MatchCollection collectionDont = Regex.Matches(donnees[i], "don\\'t\\(\\)");
                lireDebut = collectionDo.Last().Index > collectionDont.Last().Index;
                if (!lireDebut)
                {
                    donnees[i] = donnees[i].Remove(collectionDont.Last().Index);
                }
                //donnees[i] = Regex.Replace(donnees[i], @"don't\(\).*?do\(\)", "");

                //Application(donnees[i], ref resultat2);
            }
            grosseLigne = string.Join(null, donnees);
            Console.WriteLine(grosseLigne);
            grosseLigne = Regex.Replace(grosseLigne, @"don't\(\).*?do\(\)", "do()");
            Console.WriteLine(grosseLigne);
            Application(grosseLigne, ref resultat2);

            Console.WriteLine(resultat2);
        }
    }
}
