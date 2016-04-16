{��SPFA�㷨ʵ��}

{$R-,S-,Q-}
Program BOI2002_Bicriterial_routing;
Const
  Fin = 'bic.in';
  Fou = 'bic.out';
  Maxn = 100;
  MaxNode = 1280128;

Var
  Count: Array[1 .. MaxNode]of Boolean;                 {��¼ÿ�����㵱ǰ�Ƿ��ڶ�����}
  Sta: Array[1 .. MaxNode]of Longint;                   {�����·�ĸ�������}
  Dis: Array[1 .. MaxNode]of Word;                      {���·������ֵ}
  a, b, d: Array[1 .. Maxn, 1 .. Maxn]of Longint;       {���ڽӱ��ͼ}
  c: Array[1 .. Maxn]of Longint;                        {ÿ����ĳ���}
  n, s, t: Longint;

Procedure Init; {����}
  Var
    i, j, k, x, y, m: Longint;
  Begin
    Assign(Input, Fin);
    Reset(Input);
    Read(n, m, s, t);
    For k:= 1 to m do
      Begin
        Read(i, j, x, y);
        {��ÿ���߲�����������}
        Inc(c[i]);
        a[i, c[i]]:= x;
        b[i, c[i]]:= y;
        d[i, c[i]]:= j;
        Inc(c[j]);
        a[j, c[j]]:= x;
        b[j, c[j]]:= y;
        d[j, c[j]]:= i;
      End;
   Close(Input);
  End;

Procedure Main;
  Var
    v, w, w1, i, j, k, tmp, head, tail: Longint;
  Begin
    {���·����ֵ��ʼ��}
    For i:= 1 to MaxNode do
      Dis[i]:= 30000;

    {���������}
    head:= 1;
    tail:= 1;
    Sta[1]:= s;
    Dis[s]:= 0;
    Count[s]:= True;

    {SPFA�㷨��ѭ��}
    Repeat
      v:= Sta[head] And 127; {�ó���ǰ����}
      w:= Sta[head] Shr 7;   {�ó���ǰ�ķ���}
      k:= Dis[Sta[head]];    {�ó���ǰ���·��}
      For i:= 1 to c[v] do
        Begin
          w1:= w + a[v, i];
          If (w1 > 10000) then Continue; {�ȿ��ܵ����ֵ������ȥ}
          j:= w1 Shl 7 + d[v, i]; {��������ܣ��Խ�ʡ�ռ�}
          {�����ɳڲ���}
          tmp:= k + b[v, i];
          If (tmp < Dis[j]) then
            Begin
              Dis[j]:= tmp;
              If Not Count[j] then {���ڶ�������������}
                Begin
                  Count[j]:= True;
                  Inc(tail);
                  If (tail > MaxNode) then tail:= 1; {����ѭ��}
                  Sta[tail]:= j;
                End;
            End;
        End;
      Count[Sta[head]]:= False; {����Ԫ�س���}
      If (head = tail) then Break; {���п���ѭ������}
      {����ѭ��}
      Inc(head);
      If (head > MaxNode) then head:= 1;
    Until False;
  End;

Procedure Print;
  Var
    i, j, tot, min: Longint;
  Begin
    min:= 30000; {���·����Сֵ�������}
    tot:= 0;
    For i:= 0 to 10000 do {����i��������}
      Begin
        j:= i Shl 7 + t;
        If (Dis[j] < min) then {��ǰ�����·�������·����СֵС���򷽰���˫��·��}
          Begin
            min:= Dis[j]; {�������·����Сֵ}
            Inc(tot); {����˫��·������}
          End;
      End;
    Assign(Output, Fou);
    Rewrite(Output);
    Writeln(tot);
    Close(Output);
  End;

Begin
  Init;
  Main;
  Print;
End.