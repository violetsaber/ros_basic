
(cl:in-package :asdf)

(defsystem "plumbing_pub_sub_doublemsg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "pose1" :depends-on ("_package_pose1"))
    (:file "_package_pose1" :depends-on ("_package"))
    (:file "pose2" :depends-on ("_package_pose2"))
    (:file "_package_pose2" :depends-on ("_package"))
  ))