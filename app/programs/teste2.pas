program ControleFluxo;

var
   x, y : integer;
   z : real;

begin
   x := 15;
   y := 20;
   z := x * 1.5;

   if x < y then
      x := x + 1
   else
      y := y - 1;

   while z <= 50 do
   begin
      z := z + 10;
      y := y + 2;
   end;
end.
