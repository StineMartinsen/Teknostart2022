from os import path
import Pyro4
from edurov import WebMethod


def control_motors():
    """Will be started in parallel by the WebMethod class"""
    with Pyro4.Proxy("PYRONAME:KeyManager") as keys:
        with Pyro4.Proxy("PYRONAME:ROVSyncer") as rov:
            while rov.run:
                if keys.state('K_UP'):
                    UP = True
                    print('Forward')
                else:
                    UP = False
                if keys.state('K_DOWN'):
                    DOWN = True
                    print('Backward')
                else:
                    DOWN = False    
                if keys.state('K_RIGHT'):
                    RIGTH = True
                    print('Right')
                else:
                    RIGTH = False
                if keys.state('K_LEFT'):
                    LEFT = True    
                    print('left')
                else:
                    LEFT = False
                
                GPIO.output(4,UP)
                GPIO.output(5,DOWN)
                GPIO.output(6,RIGTH)
                GPIO.output(26,LEFT)   


# create the webmethod class
web_method = WebMethod(
    index_file=path.join(path.dirname(__file__), 'index.html')
)

#start serving the website, blocks the program after this point
web_method.serve()