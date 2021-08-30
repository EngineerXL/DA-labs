cp solution tests/solution
cd tests
for (( t = 1; t <= 99; t++ ));
do
	a=`cat $t.in`
	if [[ ("$a" = "") ]];
	then
		continue
	fi
	valgrind -q --tool=memcheck --leak-check=full ./solution preprocess --nodes "$t.nodes" --edges "$t.edges" --output "graph.b"
	touch out.txt
	valgrind -q --tool=memcheck --leak-check=full ./solution search --graph "graph.b" --input "$t.in" --output out.txt --full-output
	a=`diff "$t.out" -q out.txt`
	if [[ ("$a" = "") ]];
	then
		echo "Test $t OK"
	else
		echo "Test $t WA"
		break
	fi
	rm -rf "out.txt" "graph.b"
done
