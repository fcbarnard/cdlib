inherit "/std/room";

#define MAILREADER	"/d/Standard/obj/mail_reader"

string messages;
int new_mail;

create_room()
{
 
    set_short("The post office");

    set_long("\n"+
        "You are in the post office.\n"+
        "From here you can reach people with a written message, all over the universe!\n"+
        "Commands are:\n"+
        "    read            Read your mail.\n"+
        "    mail <name>     Mail to player 'name'.\n"+
        "    mail <name> -a  Mail anonymously to player 'name'. (Only for Wizards.)\n"+
        "    from            List all headers.\n"+
        "");

    add_exit("/d/Standard/start/church","north","@@wblock");

}

wblock() { return 0; }

init() {
    object reader;
    ::init();

    reader = clone_object(MAILREADER);
    if (!reader) {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());
}

leave_inv(ob, to) {
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}

query_mail(silent) {
    string name, new, sp;

    name = lower_case(call_other(this_player(), "query_name"));
    if (!restore_object("d/Standard/post_dir/" + name) || messages == "")
       return 0;
    if (silent) return 1;
    new = ""; sp = "    ";
    if (new_mail) {
	new = " NEW";
	sp = "";
    }
    write("\n"+
        "There is" + new + " mail for you in post office.\n");
    return 1;
}


