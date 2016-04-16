Program Dijkstra;
Const
  Fin = 'input.in';
  Maxn = 10000;

Type
  Link = ^Node;
  Node = Record
           v, w: Longint;                           {����ͷ���}
           Next: Link;
         End;

Var
  Q,                                                {���·����ֵ��С��}
  Q_Pos,                                            {ÿ�������ڶ��е�λ��}
  Dist,                                             {���·����ֵ}
  Fa: Array[1 .. Maxn]of Longint;                   {ÿ�������ǰ������}
  Map: Array[1 .. Maxn]of Link;                     {���ٽӱ��¼��ͼ}
  n, m, s, t, Q_Tot: Longint;

Procedure Init; {����}
  Var
    i, a, b, c: Longint;
    p: Link;
  Begin
    Assign(Input, Fin);
    Reset(Input);
    Read(n, m, s, t);
    For i:= 1 to m do
      Begin
        Read(a, b, c);

        {��ÿ������߲����������߲���}
        New(p);
        p^.v:= b; p^.w:= c;
        p^.Next:= Map[a];
        Map[a]:= p;

        New(p);
        p^.v:= a; p^.w:= c;
        p^.Next:= Map[b];
        Map[b]:= p;
      End;
    Close(Input);
  End;

Procedure Swap(i, j: Longint); {�������е�����Ԫ��i,j}
  Var
    k: Longint;
  Begin
    k:= Q[i]; Q[i]:= Q[j]; Q[j]:= k;
    Q_Pos[Q[i]]:= i;
    Q_Pos[Q[j]]:= j;
  End;

Procedure Updata(i: Longint); {������i����������λ��}
  Var
    j: Longint;
  Begin
    j:= i Shr 1;
    While (j >= 1) and (Dist[Q[j]] > Dist[Q[i]]) do
      Begin
        Swap(i, j);
        i:= j; j:= i Shr 1;
      End;
  End;

Procedure Relax(i, j, w: Longint); {�ɳڲ���}
  Begin
    If w >= Dist[j] Then Exit;
    Dist[j]:= w;
    Fa[j]:= i;
    Updata(Q_Pos[j]);
  End;

Procedure Heapfy(i: Longint); {������i�½�������λ��}
  Var
    j: Longint;
  Begin
    Repeat
      j:= i;
      {������ӱȽ�}
      If (i Shl 1 <= Q_Tot) and (Dist[Q[i Shl 1]] < Dist[Q[i]])
        Then i:= i Shl 1;
      {���Ҷ��ӱȽ�}
      If (i Shl 1 < Q_Tot) and (Dist[Q[i Shl 1 + 1]] < Dist[Q[i]])
        Then i:= i Shl 1 + 1;
      If i <> j then Swap(i, j);
    Until (i = j);
  End;

Procedure Main;
  Var
    i: Longint;
    p: Link;
  Begin
    {���·����ֵ��ʼ��}
    For i:= 1 to n do
      Begin
        Q[i]:= i;
        Q_Pos[i]:= i;
        Dist[i]:= $FFFFFF;
      End;
    Swap(1, s);    {��Դ�㽻�����Ѷ�}
    Q_Tot:= n;     {�ѵ���Ԫ����Ϊ��������n}
    Dist[s]:= 0;   

    {Dijkstra�㷨������}
    While Q_Tot > 1 do
      Begin
        i:= Q[1]; {ȡ���Ѷ�Ԫ��}

        {ɾ��ȡ����Ԫ��}
        Swap(1, Q_Tot);
        Dec(Q_Tot);

        Heapfy(1); {ά���¶�}

        {��i������ÿ���߽����ɳڲ���}
        p:= Map[i];
        While p <> Nil do
          Begin
            If (Q_Pos[p^.v] <= Q_Tot) then Relax(i, p^.v, Dist[i] + p^.w);
            p:= p^.Next;
          End;
      End;
  End;

Procedure Print(i: Longint); {�ݹ�������·������}
  Begin
    If (i = s)
      Then Write(i)
      Else Begin
        Print(Fa[i]);
        Write('--->', i);
      End;
  End;

Begin
  Init;
  Main;
  If (Dist[t] < $FFFFFF) then
    Begin
      Print(t);
      Writeln;
      Writeln('Total Cost: ', Dist[t]);
    End
  Else
    Writeln('No solution');
End.