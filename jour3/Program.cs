using System.Text.RegularExpressions;

namespace jour3
{
    internal class Program
    {
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
                var value = Regex.Matches(ligne, @"mul\(\d{1,3},\d{1,3}\)");
                for (int i = 0; i < value.Count; ++i)
                {
                    string stringValue = value[i].Value;
                    string value1 = stringValue.Substring(stringValue.IndexOf('(') + 1, stringValue.IndexOf(',') - stringValue.IndexOf('(') - 1);
                    string value2 = stringValue.Substring(stringValue.IndexOf(',') + 1, stringValue.IndexOf(')') - stringValue.IndexOf(',') - 1);

                    resultat += long.Parse(value1) * long.Parse(value2);
                }
            }

            Console.WriteLine(resultat);
        }
    }
}
