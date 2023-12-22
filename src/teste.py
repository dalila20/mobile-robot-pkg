#!/usr/bin/env python

import rospy
from sensor_msgs.msg import JointState
import numpy as np
import matplotlib.pyplot as plt

class JointStatePlotter:
    def __init__(self):
        rospy.init_node('joint_state_plotter', anonymous=True)
        self.joint_states = []

        rospy.Subscriber('/joint_states', JointState, self.joint_state_callback)

    def joint_state_callback(self, msg):
        # Recebe a mensagem JointState e extrai os dados relevantes
        self.joint_states.append(msg.position)

    def plot_data(self):
        # Plota os dados usando NumPy e Matplotlib
        joint_states_np = np.array(self.joint_states)

        # Transpõe os dados para ter um array por junta
        joint_states_np = joint_states_np.T

        # Plotagem usando Matplotlib
        plt.plot(joint_states_np)
        plt.xlabel('Tempo')
        plt.ylabel('Posição da Junta')
        plt.legend(['Junta {}'.format(i) for i in range(joint_states_np.shape[0])])
        plt.show()

if __name__ == '__main__':
    plotter = JointStatePlotter()
    rospy.spin()
