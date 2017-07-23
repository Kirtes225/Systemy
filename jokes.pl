#/usr/local/bin/perl
use LWP::Simple;
use JSON;
 
printf "Insert name of a person you want your joke to be about:\n";
$userinput1 =  <STDIN>;
chomp ($userinput1);
printf "and the last name:\n";
$userinput2 =  <STDIN>;
chomp ($userinput2);
$json = get("http://api.icndb.com/jokes/random?firstName=${userinput1}&lastName=${userinput2}");
$fact= from_json($json);
 
 
    printf $fact->{value}->{joke};
    printf "\n";
	system ("pause");
