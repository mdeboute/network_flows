Program RandomNetwork(input,netres);
{$M 16384,0,512000}
 
  Type
  ArcTreeType  = ^ArcRecord;
  ArcRecord    =
    RECORD
      ArcNumber:longint;
      ii :longint;
      jj :longint;
      cap:longint;
      LeftArcTree,RightArcTree:ArcTreeType;
    End;
 
  Var
    Arc:ArcTreeType;
    ArcTreeRoot:ArcTreeType;
    i,k,num,arcnumber:longint;
    num_arcs,num_nodes,capacity:longint;
    z:longint;
    X,Y:longint;
    xx1,xx2,xx3,xx4:longint;
    source,sink:longint;
    ch:char;
    found,example:boolean;
    found11,found22:boolean;
    OutFileName:string[20];
    netres:text;
 
  Function ArcTree(nn:longint):ArcTreeType;
    Var NewArc:ArcTreeType;
        nll,nrr:longint;
  Begin
    IF nn=0 THEN ArcTree:=nil ELSE
    Begin
      nll:=nn DIV 2; nrr:=nn-nll-1;
      xx1:=xx1+1;
      xx2:=0;xx3:=0;xx4:=0;
      NEW(NewArc);
      WITH NewArc^ DO
      Begin
        ArcNumber:=xx1;
        ii:=xx2; jj:=xx3; Cap:=xx4;
        LeftArcTree :=ArcTree(nll);
        RightArcTree:=ArcTree(nrr);
      End;
      ArcTree:=NewArc;
    End;
  End;
 
  Procedure LocateArc(t2:ArcTreeType; h2:longint);
    VAR Found2:BOOLEAN;
    Begin
      Found2:=FALSE;
      WHILE (t2<>nil) AND NOT Found2 DO
      Begin
        IF t2^.ArcNumber=h2 THEN Found2:=TRUE
        ELSE IF h2=t2^.LeftArcTree^.ArcNumber
        THEN t2:=t2^.LeftArcTree
        ELSE IF h2=t2^.RightArcTree^.ArcNumber
        THEN t2:=t2^.RightArcTree
        ELSE IF h2<t2^.RightArcTree^.ArcNumber
        THEN t2:=t2^.LeftArcTree
        ELSE IF h2>t2^.RightArcTree^.ArcNumber
        THEN t2:=t2^.RightArcTree;
      End;
      IF Found2 THEN Arc:=t2;
    End;
 
  Procedure PrintArcTree(ArcTree1:ArcTreeType);
    Begin
      IF ArcTree1<>nil THEN
      WITH ArcTree1^ DO
      Begin
        PrintArcTree(LeftArcTree);
        write(netres,'a');
        writeln(netres,ii:8,jj:8,Cap:8);
        if k<5 then Writeln(ii:5,jj:5,Cap:5);
        k:=k+1;
        z:=z+1;
        PrintArcTree(RightArcTree);
      End;
    End;
 
Procedure Randomnet;
  var complete:boolean;
      iter1,iter2:boolean;
  Procedure Add_Arc1;
    Begin
      z:=1;
      repeat
      Begin
        LocateArc(ArcTreeRoot,Z);
        IF (Arc^.ii=0) and (Arc^.jj=0) THEN
          Begin
            Arc^.ii:=X; Arc^.jj:=Y;
            Arc^.cap:=random(capacity)+1;
            IF z=num_arcs THEN complete:=true;
            z:=num_arcs;
          End;
        z:=z+1;
      End;
      until z=num_arcs+1;
    End;
 
  Procedure Add_Arc2;
    Begin
      z:=1;
      repeat
      Begin
        LocateArc(ArcTreeRoot,Z);
        IF (Arc^.ii=0) and (Arc^.jj=0) THEN
          Begin
            Arc^.ii:=Y; Arc^.jj:=X;
            Arc^.cap:=random(capacity)+1;
            IF z=num_arcs THEN complete:=true;
            z:=num_arcs;
          End;
        z:=z+1;
      End;
      until z=num_arcs+1;
    End;
 
  Begin
    iter1:=true;
    iter2:=true;
    complete:=false;
    repeat
    Begin
      Begin
        repeat
          if iter1 and iter2 then
          begin
            X:=random(num_nodes)+1; Y:=random(num_nodes)+1;
            iter2:=false;
          end
          else if iter1 and not iter2 then
          begin
            Y:=random(num_nodes)+1; X:=random(num_nodes)+1;
            iter1:=false;
            iter2:=true;
          end
          else if not iter1 and iter2 then
          begin
            X:=random(X)+1; Y:=random(Y)+1;
            iter2:=false;
          end
          else if not iter1 and not iter2 then
          begin
            Y:=random(X)+1; X:=random(Y)+1;
            iter1:=true;
            iter2:=true;
          end;
        until (Y<>X);
      End;
      IF X<>Y THEN
      Begin
        found11:=false;
        found22:=false;
        for z:=1 to num_arcs do
        Begin
          LocateArc(ArcTreeRoot,Z);
          IF ((X=Arc^.ii) and (Y=Arc^.jj)) THEN found11:=true;
        End;
        IF not found11 THEN Add_Arc1
        else if found11 then
        Begin
          for z:=1 to num_arcs do
          Begin
            LocateArc(ArcTreeRoot,Z);
            IF ((Y=Arc^.ii) and (X=Arc^.jj)) THEN found22:=true;
          End;
          IF not found22 THEN Add_Arc2;
        End;
      End;
    End;
    until complete;
  End;
 
  Procedure UserValues;
    var total_arcs:longint;
    Begin
      xx1:=0;
      writeln('  RANDOM NETWORK GENERATION');
      repeat
        write('  How many nodes are in the network: ');
        readln(num_nodes);
        if (num_nodes<=1) then
        writeln('  Try again. Need at least two nodes.');
      until (num_nodes>1);
      total_arcs:=num_nodes*num_nodes-num_nodes;
      write('  How many arcs are in the network: ');
      Begin
        repeat
          readln(num_arcs);
          if (num_arcs>total_arcs) OR (num_arcs<1) then
            Begin
              writeln('  The maximum number of arcs in a fully ');
              writeln('  dense network cannot exceed n^2-n.    ');
              writeln('  Also, you need at least one arc.');
              writeln('  Duplicate arcs and self-loops will not ');
              writeln('  be allowed.    ');
              writeln('  Try again with the number of arcs at');
              writeln('  least one, but not more than ',total_arcs,'.');
              write('  How many arcs are in the network: ');
            End;
          until ((num_arcs<=total_arcs) AND (num_arcs>=1));
      End; 
      write('  What is the upper bound for arc flow capacity: ');
      readln(capacity);
      source:=1;
      sink:=num_nodes;
      writeln(netres,'c Random Network');
      writeln(netres,'p max',num_nodes:6,num_arcs:8);
      writeln(netres,'n',source:10,'  s');
      writeln(netres,'n',sink:10,'  t');
      writeln;
      writeln('  A RANDOM NETWORK  will be generated to file ');
      writeln('  ',OutFileName,'.');
      writeln('  The number of nodes is ',num_nodes:8);
      writeln('  The number of arcs is  ',num_arcs:8);
      writeln('  The source node is node ',source,'. The sink node');
      writeln('  is numbered with the largest node number. Here the');
      writeln('  sink is node ',sink,'. The network is given as  ');
      writeln('  a list of arcs using four numbers as follows:');
      writeln('  arc tail node - arc head node - arc cost/capacity.');
      writeln('  The first few data lines look like this:');
      writeln;
      writeln('   Number of');
      writeln('   Nodes     Arcs');
      writeln(num_nodes:5,num_arcs:10);
      writeln('   Source    Sink');
      writeln(source:5,sink:10);
      writeln('   From  To  Capacity');
      writeln('   PLEASE WAIT !!!!      ');
      ArcTreeRoot:=ArcTree(num_arcs);
    End;
 
  Begin
    randomize;  {Turbo Pascal random number generator initiator.}
                {You may to replace this by compiler specific   }
                {randomizer, or write a short procedure.        }
    example:=true;
    writeln('  This program generates a RANDOM network');
    writeln('  into a user file. The network is generated');
    writeln('  by randomly pairing a given number of nodes');
    writeln('  using a given number of arcs.');
    writeln;
    writeln('  Try the network generation out by following the');
    writeln('  instructions.');
    write('  Do you want to continue (Y/N) ');
    readln(ch);
    if (ch='y') or (ch='Y') then
    Begin
      write('  Enter name of the output file: ');
      readln(OutFileName);
      assign(netres,OutFileName+'.max');
      rewrite(netres);
      UserValues;
      RandomNet;
      z:=1; k:=1;
      PrintArcTree(ArcTreeRoot);
      close(netres);
      writeln;
      writeln('  The network is completed. The data file is');
      writeln('  an ASCII file, and can be accessed with your');
      writeln('  editor. You may print the file using the DOS');
      writeln('  command PRINT ',OutFileName,'.max.');
    End;
  End.
