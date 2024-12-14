# include "Server.hpp"

int main(int argc, char const *argv[])
{
	int			port;
	std::string	password;

	if (argc != 3)
		return (std::cerr << "Usage: ./ircserv <port> <password>" << std::endl, 1);
	port = std::atoi(argv[1]);
	password = argv[2];

	try
	{
		Server server(port, password);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return 0;
}
