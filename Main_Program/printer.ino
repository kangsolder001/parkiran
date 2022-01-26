void printText()
{
  printer.setFont('A');
  printer.justify('C');
  printer.println(F("Parkir"));
  printer.println();
  printer.println("------------------------------");
  printer.justify('L');
  printer.boldOn();
  printer.print("Masuk : ");
  printer.print(String(year()));
  printer.print("-");
  printer.print(String(month()));
  printer.print("-");
  printer.print(String(day()));
  printer.print(" ");
  printer.print(String(hour()));
  printer.print(":");
  printer.print(String(minute()));
  printer.print(":");
  printer.print(String(second()));
  printer.println();
  printer.print("ID    : ");
  printer.println(now());
  printer.println("------------------------------");
  printer.println();
  printer.println();
  printer.println();
}
