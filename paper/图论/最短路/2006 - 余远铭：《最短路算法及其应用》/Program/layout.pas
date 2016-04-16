Program Usaco_Dec05_layout;
Const
  Fin = 'layout.in';
  Fou = 'layout.out';
  MaxW = 1100000000;                                     {��ִ�ķ���}
  Maxn = 1000;
  Maxm = 22000;

Var
  Dist: Array[1 .. Maxn]of Longint;                      {���·������ֵ}
  a, b, d: Array[1 .. Maxm]of Longint;                   {������¼ÿ����}
  n, m, ML, MD: Longint;

Procedure Init;
  Var
    l, i, j, k: Longint;
  Begin
    Assign(Input, Fin);
    Reset(Input);
    Read(n, ML, MD);
    m:= 0;
    {Ϊ�����ڶ�����˳���붥��˳����ͬ������ı�}
    For l:= 2 to n do
      Begin
        Inc(m);
        a[m]:= l;
        b[m]:= l - 1;
        d[m]:= 0;
      End;
    {ת�����кøеı�}
    For l:= 1 to ML do
      Begin
        Read(i, j);
        If i > j then
          Begin
            k:= i;
            i:= j;
            j:= k;
          End;
        Read(k);
        Inc(m);
        a[m]:= i;
        b[m]:= j;
        d[m]:= k;
      End;
    {ת�����з��еı�}
    For l:= 1 to MD do
      Begin
        Read(i, j);
        If i > j then
          Begin
            k:= i;
            i:= j;
            j:= k;
          End;
        Read(k);
        Inc(m);
        a[m]:= j;
        b[m]:= i;
        d[m]:= -k;
      End;
    Close(Input);
  End;

Procedure Main;
  Var
    i, tmp, tot: Longint;
    Quit: Boolean;
  Begin
    For i:= 2 to n do Dist[i]:= MaxW; {����������·��Ϊ��ִ�}
    Dist[1]:= 0;
    tot:= 0;
    {��Bellman-Ford�����·�����ж��Ƿ���ڸ�ȨȦ}
    Repeat
      Inc(tot); {�����Ѿ���ÿ���߽����ɳڲ����Ĵ���}
      Quit:= True;
      For i:= 1 to m do
        Begin
          tmp:= Dist[a[i]] + d[i];
          If tmp < Dist[b[i]] then
            Begin
              Dist[b[i]]:= tmp;
              Quit:= False; {�ж�������·������ֵ������}
            End;
        End;
    Until Quit Or (tot > n); {û�ж�����Ը������·����ֵ����ڸ�ȨȦ}

    Assign(Output, Fou);
    Rewrite(Output);
    If (tot > n) then Writeln(-1) {���ڸ�ȨȦ������Ҫ��ķ���������}
      Else
    If (Dist[n] = MaxW) then Writeln(-2) {��ǰ���·Ϊ��ִ�˵��������������}
      Else
    Writeln(Dist[n] - Dist[1]); {������ܵ�������}
    Close(Output);
  End;

Begin
  Init;
  Main;
End.