let run = () => {
  let arg_stream: Stream.t(string) =
    Stream.from(i =>
      switch (Sys.argv[i]) {
      | arg => Some(arg)
      | exception (Invalid_argument("index out of bounds")) => None
      }
    );

  switch (Stream.next(arg_stream)) {
  | cmd_name => print_endline(Printf.sprintf("Command Name: %s", cmd_name))
  | exception Stream.Failure => exit(1)
  };

  switch (Stream.empty(arg_stream)) {
  | () => print_endline("No arguments given")
  | exception Stream.Failure =>
    print_endline("Arguments:");
    let arg_printer = arg => print_endline(Printf.sprintf("• %s", arg));
    Stream.iter(arg_printer, arg_stream);
  };
};

run();