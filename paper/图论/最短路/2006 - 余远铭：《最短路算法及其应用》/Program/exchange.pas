Program Ural1162_Currency_Exchange;
Const
  Fin='';//'Input.in';
  Maxn=100;

Type
  Link=^Node;
  Node=Record
         v:Integer; {����}
         rate,less:Double; {�һ����ʺ���ת����}
         Next:Link;
       End;

Var
  Map:Array[1..Maxn]of Link; {���ڽӱ��ͼ}
  Dist:Array[1..Maxn]of Double; {���·����ֵ}
  n,s:Integer; {����������Դ��}
  v:Double; {��ʼʱӵ�еĻ�����}

Procedure Init; {����}
  Var i,j,k,m:Integer;
      p:Link;
  Begin
    Assign(Input,Fin);
    Reset(Input);
    Readln(n,m,s,v);
    New(p); p:=Nil;
    For i:=1 to n do Map[i]:=p;
    For k:=1 to m do
    Begin
      Read(i,j);
      New(p);
      Read(p^.rate,p^.less);
      p^.v:=j; p^.Next:=Map[i]; Map[i]:=p;
      New(p);
      Readln(p^.rate,p^.less);
      p^.v:=i; p^.Next:=Map[j]; Map[j]:=p;
    End;
  End;

Procedure Main; {��Bellman-Ford���·}
  Var i:Integer;
      Tt:Double;
      Quit:Boolean;
      p:Link;
  Begin
    For i:=1 to n do Dist[i]:=0; Dist[s]:=v;
    Repeat
      Quit:=True;
      For i:=1 to n do
      If Dist[i]>1e-8 Then {��ǰ������Դ��ɴ�}
      Begin
        p:=Map[i];

        {��ÿ���߽����ɳڲ���}
        While p<>Nil do
        Begin
          Tt:=(Dist[i]-p^.less)*p^.rate; {����ת�ƺ�ɵõ��Ļ�����}
          If Tt>Dist[p^.v]+1e-8 Then
          Begin
            Dist[p^.v]:=Tt;
            Quit:=False; {��¼�ô�ѭ���ж�������·����ֵ������}
          End;
          p:=p^.Next;
        End;
      End;
    Until Quit Or (Dist[s]>v+1e-8); {û�ж���ɸ��»��Ѿ��õ��ȳ�ʼ��Ļ������˳�}
    If Dist[s]>v+1e-8 Then Writeln('YES')
                      Else Writeln('NO');
  End;

Begin
  Init;
  Main;
End.