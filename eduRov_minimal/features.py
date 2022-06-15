from os import path
import Pyro4
from edurov import WebMethod


def control_motors():
    """Will be started in parallel by the WebMethod class"""
    with Pyro4.Proxy("PYRONAME:KeyManager") as keys:
        with Pyro4.Proxy("PYRONAME:ROVSyncer") as rov:
            while rov.run:
                if keys.state('K_UP'):
                    print('Forward')
                elif keys.state('K_DOWN'):
                    print('Backward')
                elif keys.state('K_RIGHT'):
                    print('Right')
                elif keys.state('K_LEFT'):
                    print('left')

# create the webmethod class
web_method = WebMethod(
    index_file=path.join(path.dirname(__file__), 'index.html')
)

#start serving the website, blocks the program after this point
web_method.serve()