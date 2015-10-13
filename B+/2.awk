BEGIN {
  printf "\\begin{tabular}{|c|c|} \n"
  printf "\\hline \n"
  printf "\\hline \n"
  printf "no of elements  &  time taken \\\\ \n"
  printf "\\hline \n"
}

{ printf $1" & "
  printf $2" \\\\ "
  printf "\n"
}

END {
  printf "\\hline \n"
}
